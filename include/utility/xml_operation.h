#ifndef XML_OPERATION_H
#define XML_OPERATION_H

#include <mxml.h>
#include "driver_match.h"

//函数接口
extern int establish_device_context(char* lid);

extern void destroy_device_context(void);

extern char* get_op_name(void);

extern int get_op_list_length(void);

extern int get_op_template_id(char* op_name);

extern void xml_operation_init(void);

extern int fill_reg_array(char* op_name, char* para_name, struct reg_array* regap);

extern int fill_plain_struct(char* op_name, char* para_name, struct st_member st[], struct_fill_func_ptr do_fill);

extern int fill_plain_array(char* op_name, char* para_name, struct plain_array* plainap);

static void create_op_name_list(void);

static void* convert_type(const char* value, const char* type);

static mxml_node_t* skip_text_node(mxml_node_t* node, char* attr);

static void find_op(char* op_name, mxml_node_t** opp);

static int find_para_list(char* para_name, mxml_node_t* op, mxml_node_t** plp);

static int find_para(mxml_node_t* op, mxml_node_t* para_list, mxml_node_t** pp, const char* name);

static void do_fill_reg_array(mxml_node_t* para, struct reg_array* regap);

static int alloc_reg_array(int len, struct reg_array** rega2p);

static int check_data_type(mxml_node_t* para, struct st_member* smp);

static int do_fill_plain_struct(mxml_node_t* para_list, mxml_node_t* op, int len,
                                struct st_member st[], struct_fill_func_ptr do_fill);
//全局变量
FILE *fp;

static mxml_node_t *tree;

static mxml_node_t *device_context;

static char** op_name_list; 

static int op_list_length;

static int counter;

#endif
