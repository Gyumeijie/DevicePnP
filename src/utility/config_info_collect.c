#include "config_info_collect.h"
#include "error_report.h"
#include "load_xml.h"
#include "miscellaneous.h"
#include <string.h>
#include <malloc.h>
#include <stdio.h>

int config_info_collect_init(void)
{ 
   device_context = NULL;
   tree = get_xml_tree(); 
   
   return SUCCESS;
}

// 建立收集设备配置信息上下文环境
int establish_device_context(char* lid)
{
    if (device_context == NULL){
        // 建立设备上下文，如果没有在配置文件中找到相应的项，则返回不匹配
        device_context = mxmlFindElement(tree,
                                         tree,
                                         "device_entity", 
                                         "lid", 
                                         lid, 
                                         MXML_DESCEND);

        //TODO 对于NULL值的检测，想一下其它的方法is_null会更好一点
        if (! check_null(__FILE__, __func__, "device_context", device_context)){
           printf("Detail: can't find configuration info for %s in xml file\n", 
                  lid);
           return FAILURE;
         }
    }
    
    // 与设备context相关的全局变量的初始化
    op_list_fetch_tracer = 0;
    op_name_list = NULL; 
    create_op_name_list();
   
    return SUCCESS;
}

// 在关闭设备上下文的时候，做一些清理工作
void destroy_device_context(void)
{
    device_context = NULL;
   
    // 与设备context相关的全局变量的清零
    op_list_fetch_tracer = 0;
    free(op_name_list);
    op_name_list = NULL;
}


// 返回当前处理的设备逻辑名，该函数是为了方便调试在设备驱动匹配过程中出
const char* get_device_context(void)
{
   return mxmlElementGetAttr(device_context, "lid");
}



// 判断设备的配置信息中是否含有global项，该函数在驱动匹配模块中被调用
Boolean has_global_config_item(void)
{
    mxml_node_t* element = mxmlFindElement(device_context,
                                           device_context,
                                           "global", 
                                           NULL, 
                                           NULL, 
                                           MXML_DESCEND);

   return (element == NULL) ? False : True;
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
      // TODO 给-1一个具体的名称，尽可能消除魔幻数
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

   // TODO 检测value是否为空
   value = mxmlElementGetAttr(node, "template_id");

   return strtoul(value, NULL, 10);
}


char* get_op_name(void)
{   
    if (op_list_fetch_tracer < op_list_length){
        return op_name_list[op_list_fetch_tracer++];
    }else{
        return NULL;
    }
}


// 为设备配置文件中的设备创建一个操作名列表
static void create_op_name_list(void)
{  
   op_list_length = get_op_list_length();
   
   // 先查找到op_name对应的op项
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
       op = get_next_sibling(op);
   }
}


void* get_first_para(void* para_list)
{
   mxml_node_t* first_para;
   first_para = get_first_child(para_list);

   if (!check_null(__FILE__, __func__, "first_para", first_para)){ 
       printf("Detail: can't find para child in xml file\n");
       return NULL;
   }

   return (void*)first_para;
}


void* find_para_list
(
   const char* dts_owner_name,
   const char* para_name
)
{  
   mxml_node_t *dts_owner, *para_list;
    
   // 查找配置信息中是否有相关的global或op配置项
   dts_owner = find_data_template_struct_owner(dts_owner_name);
   if(dts_owner == NULL) return UNMATCH;

   // 然后在op下找到para_name对应的para_list项，如果找不到则返回不匹配
   para_list = mxmlFindElement(dts_owner,
                               dts_owner,
                               "para_list",
                               "name",
                               para_name,
                               MXML_DESCEND);  
   // TODO 错误检测
   if (!check_null(__FILE__, __func__, "para_list", para_list)){
       printf("Detail: can't find para_list item named '%s' in xml file\n",
              para_name);
       return NULL;
   }

   return para_list;
}


// 因为fill_系列的函数都是填充相应数据模板结构体的函数
// 而在同一个设备上下文中，数据模板结构体可能在global或者
// op下，这个函数的功能是查找数据模板的所有者
static mxml_node_t* find_data_template_struct_owner
(
   const char* dts_owner_name
)
{
   mxml_node_t* dts_owner;

   if (is_equal(dts_owner_name, "global")){
       dts_owner = find_device_global_configuration();
   }else{
       dts_owner = find_device_operation(dts_owner_name);
   }

   if (!check_null(__FILE__, __func__, "dts_owner", dts_owner)){
       printf("Detail: can't find data template struct owner named '%s'\n", 
               dts_owner_name);
       return NULL;
   }
   
   return dts_owner;
}


int get_para_list_length(void* para_list)
{
   const char* length = mxmlElementGetAttr(para_list, "length");
   if (length != NULL){
      return strtoul(length, NULL, 10);
   }

   return -1;
}


// 通常读取一个属性列表（例如参数列表）的时候需要跳过元素节点
// 之间的文本节点
mxml_node_t* skip_text_node(mxml_node_t* node)
{ 
    mxml_node_t* sibling = node;

    while (mxmlGetType(sibling) == MXML_TEXT){
      sibling = mxmlGetNextSibling(sibling);
    }

    return sibling;
}

// 检查配置信息中参数的类型
int check_para_data_type
(
    const void* para, 
    const char* name, 
    const char* type
)
{
   const char* config_type = mxmlElementGetAttr((mxml_node_t*)para, "type");

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
   return find_element_in_device_context("op", "name", op_name);
}


void* find_device_global_configuration()
{
   return find_element_in_device_context("global", "name", "global");
}


static void* find_element_in_device_context
(
   const char* elem_name,
   const char* attr_name,
   const char* attr_val
)
{
   return  mxmlFindElement(device_context,
                           device_context,
                           elem_name,
                           attr_name,
                           attr_val, 
                           MXML_DESCEND);

}

// xml文件只是配置文件的一种，上层的代码不应该依赖与具体的xml结构
// 这里元素的数据包括xml中的属性值和文本值，如果不用xml配置文件的
// 话只要重新实现一下这个接口就行了，因为其它的配置文件形式很有可
// 能就没有text和attribute这种结构了，因此API的命名以及参数的类型
// 也要尽量通用，以应对底层配置文件格式的变化
const char* get_element_data
(
   const void* elem,
   const char* prop_name 
)
{
    if (is_equal(prop_name, "text_value")){
        return mxmlGetText((mxml_node_t*)elem, NULL);
    }

    return mxmlElementGetAttr((mxml_node_t*)elem, prop_name);
}


// 第一个元素节点
void* get_first_child (const void* parent)
{
    void* first_child = mxmlGetFirstChild((mxml_node_t*)parent);
    return (void*)skip_text_node(first_child);
}


// 下一个元素节点
void* get_next_sibling(const void* sibling)
{
    return (void*)skip_text_node(mxmlGetNextSibling((mxml_node_t*)sibling));
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
