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

extern int get_global_template_id();

extern int config_info_collect_init(void);

static void create_op_name_list(void);

extern  mxml_node_t* skip_text_node(mxml_node_t* node);

static void* find_template_data_owner
(
   const char* template_data_owner_name
);

extern void prepare_para
(
   const char* template_data_owner_name,
   const char* template_data_name,
   void** first_para, 
   int* num_para
);

extern void* find_para_list
(
   const char* template_data_owner_name,
   const char* template_data_name 
);


static void* find_template_data
(
   const char* template_data_owner_name,
   const char* template_data_name 
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

static void check_type_config
(
   const void* item,
   const char* item_name, 
   const char* expected_type
);

extern void check_template_data_type
(
   const char* template_data_owner_name,
   const char* template_data_name,
   const char* expected_type
);

extern void check_para_data_type
(
    const void* para,
    const char* para_name,
    const char* expected_type
);


extern void check_element_data_existence
(
   const char* data_name, 
   const char* data
);

extern void check_element_existence
(
   const char* element_name,
   void* element
);

static void check_existence
(
   void* item, 
   const char* msg
);


extern void report_invalid_config_info_error
(
   const char* location_info,
   const char* invalid_config_info
);


static void print_context_error_message(const char* msg);

extern void* find_element_in_context
(
   void* context,
   const char* elem_name,
   const char* attr_name,
   const char* attr_val
);

extern void* get_first_child(const void* parent);

extern void* get_next_sibling(const void* sibling);


static mxml_node_t *tree;

static mxml_node_t *device_context;

static char** op_name_list; 

static int op_list_length;

static int op_list_fetch_tracer;

#endif
