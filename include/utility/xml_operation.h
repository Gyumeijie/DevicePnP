#ifndef XML_OPERATION_H
#define XML_OPERATION_H

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

extern int xml_operation_init(void);

int fill_reg_array(char* global_or_op_name, char* para_name, 
                   struct reg_array* regap);

extern int fill_plain_struct(char* global_or_op_name, char* para_name, 
              struct struct_member st[], struct_fill_func_ptr do_fill);

extern int fill_plain_array(char* global_or_op_name, char* para_name, 
                            struct plain_array* plainap);

static void create_op_name_list(void);

static void* convert_type(const char* value, const char* type);

static mxml_node_t* skip_text_node(mxml_node_t* node, char* attr);

static int
find_global_or_op(char* global_or_op_name, mxml_node_t** global_or_op);

static int find_para_list(char* para_name, mxml_node_t* global_or_op,
                          mxml_node_t** plp);

static int find_para(mxml_node_t* global_or_op, mxml_node_t* para_list,
                     mxml_node_t** pp, const char* name);

static int do_fill_reg_array(mxml_node_t* para, struct reg_array* regap);

static int alloc_reg_array(int len, struct reg_array** rega2p);

static int check_data_type(mxml_node_t* para, char* name, char* type);

static int
do_fill_plain_struct(mxml_node_t* para_list, mxml_node_t* global_or_op, int len,
                     struct struct_member st[], struct_fill_func_ptr do_fill);

static int do_fill_plain_array(mxml_node_t* para, struct plain_array* plainap);
    
static int alloc_plain_array(int len, struct plain_array** plaina2p);

//全局变量
FILE *fp;

static mxml_node_t *tree;

static mxml_node_t *device_context;

static char** op_name_list; 

static int op_list_length;

static int counter;

#endif
