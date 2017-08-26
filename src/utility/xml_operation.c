#include "xml_operation.h"
#include <string.h>
#include <malloc.h>
#include <stdio.h>

void xml_operation_init(void)
{ 
   fp = NULL;
   tree = NULL;
   device_context = NULL;

   //在系统初始化文件init.c中被调用
   fp = fopen("device.xml", "r");
#if DEBUG
   puts((fp != NULL) ? "xml file open success!" : "open failure");
#endif
   tree = mxmlLoadFile(NULL, fp, MXML_NO_CALLBACK);
}


/**
 *　输入：设备逻辑标识符
 *　输出：无
 *  功能：建立收集设备配置信息上下文环境
 */
int establish_device_context(char* lid)
{
    if (device_context == NULL){
        //建立设备上下文，如果没有在配置文件中找到相应的项，则返回不匹配
        device_context =  mxmlFindElement(tree, tree, "device", "id", lid, MXML_DESCEND);
        if (device_context == NULL){      
#if DEBUG
            printf("Error: device '%s' has no configuration info in xml file\n", lid);
#endif
            //返回失败
            return 0;
      }
  }
    
    //与设备context相关的全局变量的初始化
    counter = 0;
    op_name_list = NULL; 
    create_op_name_list();
   
    //返回成功
    return 1;
#if DEBUG
    int i;
    int len = get_op_list_length();
    for (i=0; i<len; i++){
         printf("op_name: %s\n", get_op_name());
   }
#endif
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
 *　输出：设备配置文件中某设备的操作列表长度
 *　功能：返回设备配置文件中某设备的操作列表长度
 */
int get_op_list_length(void)
{
   mxml_node_t* node = NULL;
   const char* value = NULL;

   node = mxmlFindElement(device_context, tree, "op_list", NULL, NULL, MXML_DESCEND);
   value = mxmlElementGetAttr(node, "length");

   return strtoul(value, NULL, 10);
}


/**
 *　输入：操作名op_name
 *　输出：操作名op_name对应选择的模板id号
 *　功能：操作名op_name对应选择的模板id号
 */
int get_op_template_id(char* op_name)
{
   mxml_node_t* node = NULL;
   const char* value = NULL;

   node = mxmlFindElement(device_context, tree, "op", "name", op_name, MXML_DESCEND);
   value = mxmlElementGetAttr(node, "template_id");

   return strtoul(value, NULL, 10);
}


/**
 *　输入：无
 *　输出：无
 *　功能：依次获取设备配置文件中设备的操作名
 */
char* get_op_name(void)
{   

    if (op_name_list == NULL) return NULL;
     
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
   mxml_node_t* op = NULL;
   mxml_node_t* para_list = NULL;
   mxml_node_t* para = NULL;

   struct reg *regp = NULL;
   const char* value = NULL;
   const char* address = NULL;
   int len;

   //先查找到op_name对应的op项，如果找不到则返回不匹配
   op = mxmlFindElement(device_context, tree, "op","name", op_name, MXML_DESCEND);
   if (op == NULL){
#if DEBUG
       printf("Error: there is no op named '%s' in xml file\n", op_name);
#endif
       return 0;
   } 

   //然后在op下找到para_name对应的para_list项，如果找不到则返回不匹配
   para_list = mxmlFindElement(op, device_context, "para_list",
                                              "name", para_name, MXML_DESCEND); 
   if (para_list == NULL){
#if DEBUG
       printf("Error: there is no para_list named '%s' in xml file\n", para_name);
#endif
       return 0;
   }
   len  = strtoul(mxmlElementGetAttr(para_list, "length"), NULL, 10);
 

   //分配存储空间，如果分配失败则返回错误
   regap->len = len;
   regp = (struct reg*)malloc(sizeof(struct reg)*len);  
   if (regp == NULL) return 0;
   regap->regp = regp;

   para = mxmlFindElement(para_list, op, "para", NULL, NULL, MXML_DESCEND);
   int i;
   for (i=0; i<len; i++){
       address  = mxmlElementGetAttr(para, "address");
       //value = mxmlElementGetAttr(para, "value");
       value = mxmlGetText(para, NULL);
       regp[i].addr = strtol(address, NULL, 16);
       regp[i].val = strtol(value, NULL, 16);
#if DEBUG
       printf("reg[%d] addr: 0x%02x val: 0x%02x\n", i, regap->regp[i].addr, regap->regp[i].val);
#endif
       para = skip_text_node(para, "address");
   }

   //返回填充reg_array类型的模板参数成功
   return 1;
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
int fill_plain_struct(char* op_name, char* para_name, struct st_member st[], fill_struct func)
{
   mxml_node_t* op = NULL;
   mxml_node_t* para_list = NULL;
   mxml_node_t* para = NULL;
   void* data;
   const char* value = NULL;
   const char* type = NULL;
   int len;
     

   //先查找到op_name对应的op项，如果没有找到则返回不匹配
   op = mxmlFindElement(device_context, tree, "op", "name", op_name, MXML_DESCEND);
   if(op == NULL){
#if DEBUG
       printf("Error: there is no op named '%s' in xml file\n", op_name);
#endif
       return 0;
   }

   //然后在op下找到para_name对应的para_list项
   para_list = mxmlFindElement(op, device_context, "para_list",
                                              "name", para_name, MXML_DESCEND); 
   if (para_list == 0){    
#if DEBUG
       printf("Error: there is no para_list named '%s' in xml file\n", para_name);
#endif
       return 0;
   }

   len  = strtoul(mxmlElementGetAttr(para_list, "length"), NULL, 10);

   int i;
   int is_match = 1;
   char* name = NULL;

   //依次处理st中的成员
   for (i=0; i<len; i++){
       //检查是否有对应的结构体成员，如果没有则表示不匹配
       name = st[i].name;
       para = mxmlFindElement(para_list, op, "para", "name", name, MXML_DESCEND);
       if (para == NULL ) {
#if DEBUG
           printf("Error: there is no para named '%s' in xml file\n", name);
#endif
           is_match = 0;
           break;
       }
     
       //检查type是否一致，如果不是则表示不匹配
       type = mxmlElementGetAttr(para, "type");
       if ((type == NULL && strcmp(type, "int") != 0) || (strcmp(type, st[i].type) !=0)){
           is_match = 0;
#if DEBUG
           printf("Error: the type of '%s' should be '%s' but '%s' in xml file\n",
                                                                 name, st[i].type, type);
#endif 
           break;
       }

       //将成员的数据写入到相应的结构体中
       // value = mxmlElementGetAttr(para, "value");
       value = mxmlGetText(para, NULL);
       data = convert_type(value, type);
       func(st[i].index, data);
#if DEBUG
       printf("member: %s, value: %s\n", name, value);
#endif
       //获取下一个para项
       para = skip_text_node(para, "name");
   }
 
    return is_match;
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

   mxml_node_t* op = NULL;
   mxml_node_t* para_list = NULL;
   mxml_node_t* para = NULL;

   const char* value = NULL;
   long int *arr = NULL;
   int len;

   //先查找到op_name对应的op项，如果找不到则返回不匹配
   op = mxmlFindElement(device_context, tree, "op","name", op_name, MXML_DESCEND);
   if (op == NULL){
#if DEBUG
       printf("Error: there is no op named '%s' in xml file\n", op_name);
#endif
       return 0;
   } 

   //然后在op下找到para_name对应的para_list项，如果找不到则返回不匹配
   para_list = mxmlFindElement(op, device_context, "para_list",
                                              "name", para_name, MXML_DESCEND); 
   if (para_list == NULL){
#if DEBUG
       printf("Error: there is no para_list named '%s' in xml file\n", para_name);
#endif
       return 0;
   }
   len  = strtoul(mxmlElementGetAttr(para_list, "length"), NULL, 10);
 

   //分配存储空间，如果分配失败则返回错误
   plainap->len = len;
   arr = (long int*)malloc(sizeof(long int)*len);  
   if (arr == NULL) return 0;
   plainap->arr = arr;

   para = mxmlFindElement(para_list, op, "para", NULL, NULL, MXML_DESCEND);
   int i;
   for (i=0; i<len; i++){
       value = mxmlGetText(para, NULL);
       arr[i] = strtol(value, NULL, 10);
#if DEBUG
       printf("index: %d value: %ld\n", i, ((long int*)plainap->arr)[i]);
#endif
       para = skip_text_node(para, "type");
   }

   //返回填充reg_array类型的模板参数成功
   return 1;


}
