#ifndef CONFIG_INFO_COLLECT_H
#define CONFIG_INFO_COLLECT_H

#include <mxml.h>
#include "driver_match.h"

//函数接口
extern int establish_device_context(char* lid);

extern void destroy_device_context(void);

extern const char* get_device_context(void);

extern int has_global_config_item(void);

extern char* get_op_name(void);

extern int get_op_list_length(void);

extern int get_op_template_id(char* op_name);

extern int config_info_collect_init(void);

static void create_op_name_list(void);

extern int check_data_type
(
    mxml_node_t* para,
    const char* name,
    const char* type
);

extern  mxml_node_t* skip_text_node(mxml_node_t* node, char* attr);

//TODO 安排参数的顺序以及更好地命名
static int find_global_or_op
(
  char* global_or_op_name,
  mxml_node_t** global_or_op
);

static int find_para_list
(
  char* para_name,
  mxml_node_t* global_or_op,
  mxml_node_t** plp
);

static int get_first_para
(
  mxml_node_t* global_or_op,
  mxml_node_t* para_list,
  mxml_node_t** first_para2p,
 const char* name
);


extern int get_first_para_and_num_para 
(
   char* global_or_op_name, 
   char* para_name,
   int* num_para,
   mxml_node_t** first_para
);


extern void store_data_in_array
(   
    void* array, 
    int idx,
    void* data, 
    char* type
);
 


//全局变量
//TODO 尽可能去减少全局变量的使用
//有比较多的全局变量时，如果代码又很长，那么就需要多考虑这些全局代码在那些函数
//中修改
//如果按照填充结构进行拆分，那么就全局变量而言我们需要关注的代码就少了很多
//对应特定的填充结构而言我们就能更专注地思考其功能实现
//
//“专注”
static mxml_node_t *tree;

static mxml_node_t *device_context;

static char** op_name_list; 

static int op_list_length;

static int counter;

#endif
