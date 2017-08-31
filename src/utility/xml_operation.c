#include "utility/xml_operation.h"
#include "error_report.h"
#include <string.h>
#include <malloc.h>
#include <stdio.h>

static const char* file = "xml_operation.c";

int xml_operation_init(void)
{ 
   fp = NULL;
   tree = NULL;
   device_context = NULL;
   const char* func = "xml_operation_init";

   //在系统初始化文件init.c中被调用
   fp = fopen("device.xml", "r");
   if (!check_null(file, func, "fp", fp)){
       printf("Detail: can't open xml file\n");
       return FAILURE;
   }
   tree = mxmlLoadFile(NULL, fp, MXML_NO_CALLBACK);
   
   return SUCCESS;
}


/**
 *　输入：设备逻辑标识符
 *　输出：无
 *  功能：建立收集设备配置信息上下文环境
 */
int establish_device_context(char* lid)
{
    const char* func = "establish_device_context";

    if (device_context == NULL){
        //建立设备上下文，如果没有在配置文件中找到相应的项，则返回不匹配
        device_context =  mxmlFindElement(tree, tree, "device", "id", lid, MXML_DESCEND);
        if (!check_null(file, func, "device_context", device_context)){
            printf("Detail: can't find configuration info for %s in xml file\n", lid);
        
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


const char* get_device_context()
{
   return mxmlElementGetAttr(device_context, "id");
}


int get_op_list_length(void)
{
   mxml_node_t* node = NULL;
   const char* value = NULL;

   node = mxmlFindElement(device_context, tree, "op_list", NULL, NULL, MXML_DESCEND);
   value = mxmlElementGetAttr(node, "length");

   return strtoul(value, NULL, 10);
}


int get_op_template_id(char* op_name)
{
   mxml_node_t* node = NULL;
   const char* value = NULL;

   node = mxmlFindElement(device_context, tree, "op", "name", op_name, MXML_DESCEND);
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
   mxml_node_t* op = NULL;
   const char* val = NULL;
   
   op_list_length = get_op_list_length();
   
   //先查找到op_name对应的op项
   op = mxmlFindElement(device_context, tree, "op", NULL, NULL, MXML_DESCEND);
   
   op_name_list =(char**) malloc(sizeof(char*)*op_list_length);
   
   int i;
   for (i=0; i<op_list_length; i++){   
      val =  mxmlElementGetAttr(op, "name");
      op_name_list[i] =(char*)val;
      op = skip_text_node(op, "name");
   }
}


/**
 *　输入：操作名op_name，模板参数para_list的名字para_name以及一个reg_array数据结构
 *        的指针
 *　输出：填充类型为reg_array的模板参数是否成功
 *　功能：为给定操作名填充类型为reg_array的模板参数
 */
int fill_reg_array(char* op_name, char* para_name, struct reg_array* regap)
{
   mxml_node_t *op, *para_list, *para;
   struct reg *regp;
   const char* func = "fill_reg_array";

   find_op(op_name, &op);

   //然后在op下找到para_name对应的para_list项，如果找不到则返回不匹配
   if(!find_para_list(para_name, op, &para_list)) return UNMATCH;
   int len  = strtoul(mxmlElementGetAttr(para_list, "length"), NULL, 10);
 

   //分配存储空间，如果分配失败则返回错误
   if(!alloc_reg_array(len, &regap)) return UNMATCH;

   //获取para_list的第一个para
   if(!find_para(op, para_list, &para, NULL)) return UNMATCH;

   //填充reg_array类型的模板参数
   do_fill_reg_array(para, regap);

   return MATCH;
}


static int
find_para(mxml_node_t* op, mxml_node_t* para_list, mxml_node_t** pp, const char* name)
{
    char* attr = (name == NULL) ?  NULL : "name";
    const char* func = "find_para";
    const char* value = name;

    *pp = mxmlFindElement(para_list, op, "para", attr, value, MXML_DESCEND);
    if (!check_null(file, func, "para", *pp)){
       (name == NULL) ? printf("Detail: can't find para child in xml file\n")
                      : printf("Detail: can't find para named '%s' in xml file\n", name);
       return FAILURE;
   }

   return SUCCESS;
}


static int alloc_reg_array(int len, struct reg_array** rega2p)
{
   struct reg *regp;
   const char* func = "alloc_reg_array";

   (*rega2p)->len = len;
   regp = (struct reg*)malloc(sizeof(struct reg)*len);  
   if (!check_null(file, func, "regp", regp)) return FAILURE;
   (*rega2p)->regp = regp;

    return SUCCESS;
}


static int do_fill_reg_array(mxml_node_t* para, struct reg_array* regap)
{
   int i, len;
   struct reg *regp;
   const char *value, *address;
   const char* func = "do_fill_reg_array";

   len = regap->len;
   regp = regap->regp;
   for (i=0; i<len; i++){
       address  = mxmlElementGetAttr(para, "address");
       if(!check_null(file, func, "address", address)) return FAILURE;

       value = mxmlGetText(para, NULL);
       if(!check_null(file, func, "value", value)) return FAILURE;

       regp[i].addr = strtol(address, NULL, 16);
       regp[i].val = strtol(value, NULL, 16);

       para = skip_text_node(para, "address");
    }

    return SUCCESS;
}


static void find_op(char* op_name, mxml_node_t** opp)
{
   //没有必要检测oop, driver_match的find_and_exec_match_func会检测
   *opp = mxmlFindElement(device_context, tree, "op","name", op_name, MXML_DESCEND);
}



static int find_para_list(char* para_name, mxml_node_t* op, mxml_node_t** plp)
{
   const char* func = "find_para_list";

   //然后在op下找到para_name对应的para_list项，如果找不到则返回不匹配
   *plp = mxmlFindElement(op, device_context, "para_list",
                                              "name", para_name, MXML_DESCEND);  
   if (!check_null(file, func, "para_list", *plp)){
       printf("Detail: can't find para_list item named '%s' in xml file\n", para_name);
       return FAILURE;
   }

   return SUCCESS;
}



/**
 *　输入：xml解析树中的一个节点node以及节点的属性attr
 *　输出：返回node的第一个非文本类型的兄弟节点指针
 *　功能：当遍历列表的时候，因为xml中列表项中间有text类型的节点，需要将其过滤掉
 *　说明：如果仅仅通过mxmlGetText来跳过text类型的节点有时候不太可靠，所以加上
 *  　　　表项节点的某一属性attr，因为text类型节点没有属性因此可以将其可靠地过滤
 */
static mxml_node_t* skip_text_node(mxml_node_t* node, char* attr)
{ 
   mxml_node_t* sibling = NULL;
   sibling = mxmlGetNextSibling(node);
 
   while(mxmlGetText(sibling, NULL) != NULL){
      //找到第一个非文本类型的节点
      if (mxmlElementGetAttr(sibling, attr) != NULL){
          break;
      }

      sibling = mxmlGetNextSibling(sibling);
   }

   return sibling;   
}


/**
 *　输入：操作名op_name，模板参数para_list的名字para_name，包含驱动模板中待收集的
 *        类型为struct的模板参数的每个成员信息结构体数组st以及执行具体填充工作的
 *        函数func
 *　输出：填充类型为struct的模板参数是否成功
 *　功能：为给定操作名填充类型为struct的模板参数
 */
int fill_plain_struct(char* op_name, char* para_name, struct struct_member st[],
                      struct_fill_func_ptr do_fill)
{
   mxml_node_t *op, *para_list, *para;
   void* data;
   const char *value, *type;
   const char* func = "fill_plain_struct";

   find_op(op_name, &op);

   //然后在op下找到para_name对应的para_list项
   if(!find_para_list(para_name, op, &para_list)) return UNMATCH;
   int len  = strtoul(mxmlElementGetAttr(para_list, "length"), NULL, 10);
 
   if(!do_fill_plain_struct(para_list, op, len, st, do_fill)) return UNMATCH;

   return MATCH;
}


static int do_fill_plain_struct(mxml_node_t* para_list, mxml_node_t* op, int len,
                                struct struct_member st[], struct_fill_func_ptr do_fill)
{

   void* data;
   const char *name, *value;
   const char* func = "do_fill_plain_struct";
   mxml_node_t* para;

   //依次处理st中的成员
   int i;
   for (i=0; i<len; i++){
       //检查是否有对应的结构体成员，如果没有则表示不匹配
       name = st[i].name;
       if(!find_para(op, para_list, &para, name)) return FAILURE;
       
       //检查type是否一致，如果不是则表示不匹配
       if(!check_data_type(para, st[i].name, st[i].type)) return FAILURE;

       //将成员的数据写入到相应的结构体中
       value = mxmlGetText(para, NULL);
       data = convert_type(value, st[i].type);
       do_fill(st[i].index, data);
       
       //获取下一个para项
       para = skip_text_node(para, "name");
   }

    return SUCCESS;
}


static int check_data_type(mxml_node_t* para, char* name, char* type)
{
   const char* config_type;
   const char* func = "check_data_type";

   config_type = mxmlElementGetAttr(para, "type");
   if (!check_null(file, func, "type", config_type)){
       printf("Detail: can't resolve the type of '%s'\n", name);
       return FAILURE;
   }

   if (strcmp(config_type, type)){
       report_error(file, func, "bad type!");
       printf("Detail: the type of '%s' should be '%s', but not '%s'\n",
                                           name, type, config_type);
       return FAILURE;
    }

   return SUCCESS;
}



/**
 *　输入：xml节点的属性值指针value和该节点在驱动程序中的数据类型type
 *　输出：一个void类型的指针，指针指向类型转换过的变量
 *　功能：将xml节点的属性值转换成正确的数据类型
 */
static void* convert_type(const char* value, const char* type)
{
      static long int data_i;
      static float data_f;
      static char data_c;
      void* data;
 
      if (strcmp(type, "char") == 0){
           data_c = strtoul(value, NULL, 16);
           data = &data_c;
       }else if(strcmp(type, "float") == 0){
           data_f = strtod(value, NULL);
           data = &data_f;
       }else{
           data_i = strtoul(value, NULL, 10);
           data = &data_i;
       }

       return data;
}



int fill_plain_array(char* op_name, char* para_name, struct plain_array* plainap)
{

   mxml_node_t *op, *para_list, *para;


   //先查找到op_name对应的op项，如果找不到则返回不匹配
   find_op(op_name, &op);

   //然后在op下找到para_name对应的para_list项，如果找不到则返回不匹配
   if(!find_para_list(para_name, op, &para_list)) return UNMATCH;
   int len  = strtoul(mxmlElementGetAttr(para_list, "length"), NULL, 10);

   //分配存储空间，如果分配失败则返回错误
   if (!alloc_plain_array(len, &plainap)) return UNMATCH;
   
   //获取para_list的第一个para
   if (!find_para(op, para_list, &para, NULL)) return UNMATCH;
   
   //填充plain_array类型的模板参数
   if(!do_fill_plain_array(para, plainap)) return UNMATCH;

   return MATCH;
}


static int 
do_fill_plain_array(mxml_node_t* para, struct plain_array* plainap)
{

   int i;
   const char* value;
   void* arr = plainap->arr;
   int len = plainap->len;
   char* type = plainap->type;
   void* data;

   for (i=0; i<len; i++){
       value = mxmlGetText(para, NULL);

       //检查type是否一致，如果不是则表示不匹配
       if(!check_data_type(para, "plain_array", type)) return FAILURE;
       
       data = convert_type(value, type);
       if (!strcmp(type, "char")){
           ((char*)arr)[i] = *(char*)data;
       }else if(!strcmp(type, "int")){
           ((int*)arr)[i] = *(int*)data;
       }else{
           ((float*)arr)[i] = *(float*)data;
       }
       
       para = skip_text_node(para, "type");
   }

   return SUCCESS;
}


static int alloc_plain_array(int len, struct plain_array** plaina2p)
{
   void* arr;
   const char* func = "alloc_reg_array";

   (*plaina2p)->len = len;
   arr = malloc(sizeof(long int)*len);  
   if (!check_null(file, func, "arr", arr)) return FAILURE;
   (*plaina2p)->arr = arr;
   
   return SUCCESS;
}
