#include "config_info_collect.h"
#include "error_report.h"
#include "load_xml.h"
#include "miscellaneous.h"
#include <string.h>
#include <malloc.h>
#include <stdio.h>

//TODO 分离开来使得每种格式的数据填充都是单独一个文件
//这样后续用户如果想要扩展的行的格式就不用改这个文件了
//而是新建一些特定的文件就可以工作
//分离“可变”和“不变”的部分
//原来的这个文件只提供一些工具函数

int config_info_collect_init(void)
{ 
   device_context = NULL;
   tree = get_xml_tree(); 
   
   return SUCCESS;
}


/**
 *　输入：设备逻辑标识符
 *　输出：无
 *  功能：建立收集设备配置信息上下文环境
 */
int establish_device_context(char* lid)
{
    //TODO 检测lid
    if (device_context == NULL){
        //建立设备上下文，如果没有在配置文件中找到相应的项，则返回不匹配
        device_context =  mxmlFindElement(tree,
                                          tree,
                                          "device_entity", 
                                          "lid", 
                                          lid, 
                                          MXML_DESCEND);
        //对于NULL值的检测，想一下其它的方法
        // is_null = 
        if (!check_null(__FILE__, __func__, "device_context", device_context)){
           printf("Detail: can't find configuration info for %s in xml file\n", 
                  lid);
           return FAILURE;
         }
    }
    
    //与设备context相关的全局变量的初始化
    counter = 0;
    op_name_list = NULL; 
    create_op_name_list();
   
    return SUCCESS;
}


/**
 *　输入：无
 *　输出：无
 *　功能：在关闭设备上下文的时候，做一些清理工作
 */ 
void destroy_device_context(void)
{
    device_context = NULL;
   
    //与设备context相关的全局变量的清零
    counter = 0;
    free(op_name_list);
    op_name_list = NULL;
}


/**
 *　输入：无
 *　输出：当前处理的设备逻辑名
 *　功能：返回当前处理的设备逻辑名，该函数是为了方便调试在设备驱动匹配过程中出
 *　　　　现的错误
 */
const char* get_device_context(void)
{
   return mxmlElementGetAttr(device_context, "lid");
}


/**
 *　输入：无
 *　输出：返回一个整数表示条件是否满足
 *　功能：判断设备的配置信息中是否含有global项，该函数在驱动匹配模块中被调用
 */
// TODO 尝试一下global
int has_global_config_item(void)
{
    mxml_node_t* element = mxmlFindElement(device_context,
                                           device_context,
                                           "global", 
                                           NULL, 
                                           NULL, 
                                           MXML_DESCEND);

   return (element == NULL) ? 0 : 1;
}


int get_op_list_length(void)
{

   mxml_node_t* node = mxmlFindElement(device_context, 
                                       device_context,
                                       "op_list",
                                       NULL,
                                       NULL, 
                                       MXML_DESCEND);
   if(! check_null(__FILE__, __func__, "node", node)) {
      printf("Detail: can't not find para_list item in xml file\n");
      //TODO 给-1一个具体的名称，尽可能消除魔幻数
      return -1;
   }

   const char* value = mxmlElementGetAttr(node, "length");
   return strtoul(value, NULL, 10);
}


int get_op_template_id(char* op_name)
{
   mxml_node_t* node = NULL;
   const char* value = NULL;

   node = mxmlFindElement(device_context, 
                          device_context,
                          "op", 
                          "name",
                          op_name,
                          MXML_DESCEND);
   value = mxmlElementGetAttr(node, "template_id");

   return strtoul(value, NULL, 10);
}


char* get_op_name(void)
{   
    if (counter < op_list_length){
        return op_name_list[counter++];
    }else{
        return NULL;
    }
}


/**
 *　输入：无
 *　输出：无
 *　功能：为设备配置文件中的设备创建一个操作名列表
 */
static void create_op_name_list(void)
{  
   op_list_length = get_op_list_length();
   
   //先查找到op_name对应的op项
   mxml_node_t* op = mxmlFindElement(device_context,
                                     device_context,
                                     "op",
                                     NULL,
                                     NULL, 
                                     MXML_DESCEND);
   
   op_name_list =(char**) malloc(sizeof(char*)*op_list_length);
   
   int i;
   for (i=0; i<op_list_length; i++){   
       const char* op_name =  mxmlElementGetAttr(op, "name");
       op_name_list[i] =(char*)op_name;
       op = skip_text_node(mxmlGetNextSibling(op), "name");
   }
}


static int get_first_para
(
    mxml_node_t* global_or_op, 
    mxml_node_t* para_list,
    mxml_node_t** first_para2p,
    const char* name
)
{
    char* attr = (name == NULL) ?  NULL : "name";
    const char* value = name;

    (*first_para2p)= mxmlFindElement(para_list, para_list, "para", 
                                     attr, value, MXML_DESCEND);
    if (!check_null(__FILE__, __func__, "first_para", (*first_para2p))){
          (name == NULL) 
             ? printf("Detail: can't find para child in xml file\n")
             : printf("Detail: can't find para named '%s' in xml file\n", name);
       return FAILURE;
   }

   return SUCCESS;
}


static int find_para_list
(
   char* para_name,
   mxml_node_t* global_or_op, 
   mxml_node_t** plp
)
{
   //然后在op下找到para_name对应的para_list项，如果找不到则返回不匹配
   *plp = mxmlFindElement(global_or_op, global_or_op, "para_list",
                          "name", para_name, MXML_DESCEND);  
   if (!check_null(__FILE__, __func__, "para_list", *plp)){
       printf("Detail: can't find para_list item named '%s' in xml file\n",
              para_name);
       return FAILURE;
   }

   return SUCCESS;
}


//TODO 进行重构
static int find_global_or_op
(
   char* global_or_op_name, 
   mxml_node_t** global_or_op
)
{
   const  char* elem_name;

   (strcmp(global_or_op_name, "global") != 0) 
         ? (elem_name = "op") 
         : (elem_name = "global"); 
   *global_or_op = mxmlFindElement(device_context, device_context, elem_name,
                                  "name", global_or_op_name, MXML_DESCEND);
   if (!check_null(__FILE__, __func__, "global_or_op", *global_or_op)){
       printf("Detail: can't find global_or_op named '%s' in xml file\n", 
               global_or_op_name);
       return FAILURE;
   }
   
   return SUCCESS;
}


// TODO 修改成get_first_child
int get_first_para_and_num_para 
(
   char* global_or_op_name, 
   char* para_name,
   int* num_para,
   mxml_node_t** first_para
)
{

   mxml_node_t *global_or_op, *para_list;
    
   //查找配置信息中是否有相关的global或op配置项
   if(!find_global_or_op(global_or_op_name, &global_or_op)) return UNMATCH;

   //然后在op下找到para_name对应的para_list项，如果找不到则返回不匹配
   if(!find_para_list(para_name, global_or_op, &para_list)) return UNMATCH;
   (*num_para) = strtoul(mxmlElementGetAttr(para_list, "length"), NULL, 10);
 
   //获取para_list的第一个para
   return get_first_para(global_or_op, para_list, first_para, NULL);
}


// 通常读取一个属性列表（例如参数列表）的时候
mxml_node_t* skip_text_node(mxml_node_t* node, char* attr)
{ 
    mxml_node_t* sibling = node;

    while (mxmlGetType(sibling) == MXML_TEXT){
      sibling = mxmlGetNextSibling(sibling);
    }

    return sibling;
}


//TODO 如果需要区分符号，这里还需要改进
//尽量写成工具函数不要与具体的细节耦合太紧
void store_data_in_array
(
    void* array, 
    int idx, 
    void* data, 
    char* type
)
{  
    if (is_equal(type, "char")){
        ((char*)array)[idx] = *(char*)data;
    }else if(is_equal(type, "int")){
        ((int*)array)[idx] = *(int*)data;
    }else if(is_equal(type, "float")){
        ((float*)array)[idx] = *(float*)data;
    }else{
       //
    }
}

/**
 *　输入：参数名name, 配置信息中参数项指针para以及设备驱动中要求的类型type
 *　输出：返回一个整数表示配置的参数类型是否与设备驱动要求的参数类型相同
 *　功能：检查配置信息中参数的类型
 */
//TODO 名字与其所做的是不太符合，选一个好的名字
int check_data_type
(
    mxml_node_t* para, 
    const char* name, 
    const char* type
)
{
   const char* config_type;

   config_type = mxmlElementGetAttr(para, "type");
   if (! check_null(__FILE__, __func__, "type", config_type)){
       printf("Detail: can't resolve the type of '%s'\n", name);
       return FAILURE;
   }

   if (! is_equal(config_type, type)){
       report_error(__FILE__, __func__, "bad type!");
       printf("Detail: the type of '%s' should be '%s', but not '%s'\n",
               name, type, config_type);
       return FAILURE;
    }

   return SUCCESS;
}




// 用于查找相应的驱动函数的配置项目，op_name是要查找的驱动函数名
void* find_device_operation(const char* op_name)
{
   return  mxmlFindElement(device_context,
                           device_context,
                           "op",
                           "name",
                            op_name, 
                            MXML_DESCEND);
}


// xml文件只是配置文件的一种，上层的代码不应该依赖与具体的xml结构
// 这里元素的数据包括xml中的属性值和文本值，如果不用xml配置文件的
// 话只要重新实现一下这个接口就行了，因为其它的配置文件形式很有可
// 能就没有text和attribute这种结构了，因此API的命名以及参数的类型
// 也要尽量通用，以应对底层配置文件格式的变化
const char* get_element_data
(
   void* elem,
   const char* prop_name 
)
{
    if (is_equal(prop_name,"text_value")){
        return mxmlGetText(elem, NULL);
    }

    return mxmlElementGetAttr(elem, prop_name);
}


// 第一个元素节点
void* get_first_child (void* parent)
{
    void* first_child = mxmlGetFirstChild(parent);
    return (void*)skip_text_node(first_child, "id");
}


//下一个元素节点
void* get_next_sibling(void* sibling)
{
    return (void*)skip_text_node(mxmlGetNextSibling(sibling), "id");
}


// 对于比较顶层的一些结构如函数操作列表，函数操作项目，参数列表
// 全局配置项目，单个代码块， 代码块组都可单独提供一个函数去操作
// 它们
void* find_element_in_operation_context
(
   void* op_context,
   const char* elem_name
)
{
   return  mxmlFindElement(op_context,
                           op_context,
                           elem_name,
                           NULL,
                           NULL, 
                           MXML_DESCEND);
}

