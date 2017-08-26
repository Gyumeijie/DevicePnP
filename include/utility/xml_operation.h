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

extern int fill_plain_struct(char* op_name, char* para_name, struct st_member st[], fill_struct func);

extern int fill_plain_array(char* op_name, char* para_name, struct plain_array* plainap);

static void create_op_name_list(void);

static void* convert_type(const char* value, const char* type);

static mxml_node_t* skip_text_node(mxml_node_t* node, char* attr);

//全局变量
FILE *fp;

static mxml_node_t *tree;

static mxml_node_t *device_context;

static char** op_name_list; 

static int op_list_length;

static int counter;

#endif
