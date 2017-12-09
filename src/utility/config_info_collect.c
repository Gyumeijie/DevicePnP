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
       device_context = find_element_in_context(tree,
                                                "device_entity", 
                                                "lid", 
                                                lid); 

       check_existence(device_context, "can't establish device context"); 
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
    
  void* global = find_element_in_device_context("global", NULL, NULL);

   return (global == NULL) ? False : True;
}


int get_op_list_length(void)
{

   void* op_list = find_element_in_device_context("op_list", NULL, NULL);
   check_existence(op_list, "can't find op_list");

   const char* length_str = get_element_data(op_list, "length");
   check_element_data_existence("length", length_str);

   return strtoul(length_str, NULL, 10);
}


int get_op_template_id(char* op_name)
{

   void* op = find_element_in_device_context("op", "name", op_name);

   const char* template_id_str = get_element_data(op, "template_id");
   check_element_data_existence("template_id", template_id_str);

   return strtoul(template_id_str, NULL, 10);
}


int get_global_template_id()
{
   void* global = find_element_in_device_context("global", NULL, NULL);

   const char* template_id_str = get_element_data(global, "template_id");
   check_element_data_existence("template_id", template_id_str);

   return strtoul(template_id_str, NULL, 10);
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
   void* op = find_element_in_device_context("op", NULL, NULL);

   op_list_length = get_op_list_length();
   op_name_list = malloc(sizeof(char*)*op_list_length);
   check_malloc(op_name_list);
   
   int i;
   for (i=0; i<op_list_length; i++){   
       const char* op_name_str = get_element_data(op, "name");
       check_element_data_existence("op_name", op_name_str);
       op_name_list[i] =(char*)op_name_str;

       op = get_next_sibling(op);
   }
}


void prepare_para
(
   const char* template_data_owner_name,
   const char* template_data_name,
   void** first_para, 
   int* num_para
)
{
   void* para_list = find_para_list(template_data_owner_name,
                                    template_data_name);

   check_element_existence("para_list", para_list);

   *num_para = get_para_list_length(para_list);
   *first_para = get_first_para(para_list);
}


void* get_first_para(void* para_list)
{
   void* first_para = get_first_child(para_list);
   check_element_existence("para", first_para);
   
   return first_para;
}


void* find_para_list
(
   const char* template_data_owner_name,
   const char* template_data_name 
)
{  
   void *para_list, *template_data;

   template_data = find_template_data(template_data_owner_name,
                                      template_data_name); 

   para_list = find_element_in_context(template_data,"para_list", NULL, NULL);
   check_existence(para_list, "can't find para_list");

   return para_list;
}


static void* find_template_data
(
   const char* template_data_owner_name,
   const char* template_data_name 
)
{
   void *template_data_owner, *template_data;

   template_data_owner = find_template_data_owner(template_data_owner_name);

   template_data = find_element_in_context(template_data_owner, 
                                           "template_data",
                                            "name",
                                            template_data_name);
   check_element_existence("template_data", template_data);

   return template_data;
}


// 因为fill系列的函数都是填充相应数据模板结构体的函数,而在同一个
// 设备上下文中，模板数据可能在global或者op下，这个函数的功能是
// 查找模板的所有者
static void* find_template_data_owner
(
   const char* template_data_owner_name
)
{
   void* template_data_owner;

   if (is_equal(template_data_owner_name, "global")){
       template_data_owner = find_device_global_configuration();
   }else{
       template_data_owner = find_device_operation(template_data_owner_name);
   }

   // 因为如果template_data_owner_name不存在的话，就不会调用相应的匹配函数
   // 所以这里肯定能够找到template_data_owner,不必检测其是否存在
   
   return template_data_owner;
}


int get_para_list_length(void* para_list)
{
   const char* length_str = get_element_data(para_list, "length");
   check_element_data_existence("length", length_str);

   return strtoul(length_str, NULL, 10);

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
   return find_element_in_context(device_context,
                                  elem_name,
                                  attr_name,
                                  attr_val);

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
void* find_element_in_context
(
   void* context,
   const char* elem_name,
   const char* attr_name,
   const char* attr_val
)
{
   return  mxmlFindElement(context,
                           context,
                           elem_name,
                           attr_name,
                           attr_val, 
                           MXML_DESCEND);
}


// 使用下面几个check函数对配置信息的合法性进行检查

void check_template_data_type
(
   const char* template_data_owner_name,
   const char* template_data_name,
   const char* expected_type
)
{
   void* template_data = find_template_data(template_data_owner_name,
                                            template_data_name);  

   check_type_config(template_data, template_data_name, expected_type);
}


void check_para_data_type
(
   const void* para,
   const char* para_name,
   const char* expected_type
)
{
   check_type_config(para, para_name, expected_type);
}


static void check_type_config
(
   const void* item,
   const char* item_name, 
   const char* expected_type
)
{
   const char* type_str = get_element_data(item, "type");
   check_element_data_existence("type", type_str);

   if (is_not_equal(expected_type, type_str)){
       char msg[128];
       sprintf(msg,
               "Bad type: the type of '%s' should be '%s', but not '%s'",
               item_name, expected_type, type_str);

       print_context_error_message(msg); 

       exit(1);
    }
}


void check_element_data_existence
(
   const char* data_name, 
   const char* data
)
{
    char msg[64];
    sprintf(msg, "element data '%s' is missing", data_name);

    check_existence((void*)data, msg);
}


void check_element_existence
(
   const char* element_name,
   void* element
)
{
    char msg[64];
    sprintf(msg, "element '%s' is not found", element_name);

    check_existence(element, msg);
}


static void check_existence
(
   void* item, 
   const char* msg
)
{
  if (item == NULL){
     print_context_error_message(msg);
     exit(1);
  }
}


static void print_context_error_message(const char* msg)
{
   const char* dev_context = get_device_context();
   const char* tdo_context = get_template_data_owner_context();

   fprintf(stderr, "<Error configuration_context=\"%s@%s\">\n", 
                    tdo_context, 
                    dev_context);
   fprintf(stderr, "  <Message>%s</Message>\n", msg);
   fprintf(stderr, "</Error>\n");
}
