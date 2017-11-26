#ifndef CONFIG_INFO_COLLECT_H
#define CONFIG_INFO_COLLECT_H

#include <mxml.h>
#include "driver_match.h"

// 函数接口
extern int establish_device_context(char* lid);

extern void destroy_device_context(void);

extern const char* get_device_context(void);

extern Boolean has_global_config_item(void);

extern char* get_op_name(void);

extern int get_op_list_length(void);

extern int get_op_template_id(char* op_name);

extern int config_info_collect_init(void);

static void create_op_name_list(void);

extern int check_para_data_type
(
    const void* para,
    const char* name,
    const char* type
);

extern  mxml_node_t* skip_text_node(mxml_node_t* node);

static mxml_node_t* find_data_template_struct_owner
(
   const char* dts_owner_name
);

extern void* find_para_list
(
   const char* dts_owner_name,
   const char* para_name
);

extern void* get_first_para(void* para_list);

static void* find_element_in_device_context
(
   const char* elem_name,
   const char* attr_name,
   const char* attr_val
);

extern int get_para_list_length(void* para_list);

extern void* find_device_global_configuration();

extern void* find_device_operation(const char* op_name);

extern const char* get_element_data
(
   const void* elem,
   const char* prop_name 
);


extern void* find_element_in_operation_context
(
   void* op_context,
   const char* elem_name
);

extern void* get_first_child(const void* parent);

extern void* get_next_sibling(const void* sibling);


static mxml_node_t *tree;

static mxml_node_t *device_context;

static char** op_name_list; 

static int op_list_length;

static int op_list_fetch_tracer;

#endif
