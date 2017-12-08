#ifndef DRIVER_MATCH_H
#define DRIVER_MATCH_H

#include "types.h"

#define MATCH 1
#define UNMATCH 0

#define MAX_TEMPLATE_NAME_LENGTH 64


// 定义填充结构体的函数类型
typedef void (*fill_struct_function)(int, void*);

// 定义模板匹配函数类型
typedef int (*match_function)(void);

// 定义寄存器结构
struct reg{
  char addr;
  char val;
};

// 定义收集设备配置文件中类型为register_array的para_list的结构体
struct register_array{
    int len; 
    struct reg* regp;
};


// 定义收集设备配置文件中类型为plain_array的para_list的结构体
struct plain_array{
    int len;
    void* arr;
    char* type;
};


// 定义代码块结构
struct group_code_blocks{
   int num_block;
   const char** code_block_src_array; // 存放各个代码块源码的数组
   int** compiled_byte_code_array; // 存放各个代码块编译后的字节码的数组
};


struct single_code_block{
   const char* code_block_src;
   int* compiled_byte_code;
};


// 定义命令序列描述结构体
struct extra_command_description{
   short int size;
   short int compute_id;
};


struct command_description{    
    char occupied_by[12];
    struct extra_command_description extra_cmd_desc;
};


// 定义收集设备配置文件中类型为command_sequence的para_list的结构体
struct command_sequence{
    int bytes_size;
    unsigned char* bytes_value;
    struct command_description* cmd_seq_desc;
    struct group_code_blocks* compute_funcs;
};


// 字节组装描述信息
struct bytes_assembly_descriptor{
   short int num_byte;
   short int start;
   short int process_id;
};


// 字节数组组装方案
struct bytes_array_assembly_scheme{
   short int num_para;
   struct bytes_assembly_descriptor* bytes_asm_descs;
   struct single_code_block* precondition;
   struct group_code_blocks* postprocess_funcs;
};

// 定义收集设备配置文件中类型为struct的para_list的结构体
struct struct_member{
    char* type;
    char* name;
    int index;
};


// 定义模板匹配结构体
struct template_match{
    char* name;
    match_function match_func;
};


// 定义描述设备驱动的最小功能集结构体
struct min_function_set{
  int required_ops;
  int required_ops_num;
  int* required_ops_index;
  const char** required_ops_name;
};


// 定义模板参数结构体
struct data_template{
    int template_id;
    void* para_struct;
};


// 匹配信息结构体
struct match_info{
 int data_table_size;
 struct template_match* match_funcs_table;
 int match_funcs_num;
 struct min_function_set* mfsp;
 int* complementation_record;
};

static void undo_match(void);

static void init_data_template_table(int dtsize);

static match_function find_match_function
(
   char* template_name,
   struct match_info* mip 
);

static void construct_template_name
(  
   char* template_name,
   char* name, 
   int template_id
);

static int tackle_global_configuration(struct match_info* mip);

static int try_match
(
   char* template_name,
   struct match_info* mip 
);

static int has_all_required_operations_complemented(struct match_info* mip);

extern int check_match
(
   int status, 
   int op_idx, 
   int template_id,
   void* data_template
);

extern int do_match(struct match_info* mip); 

extern void* get_data_template_table(void);

extern const char* get_op_context();

extern int has_operation_complemented
(  
    struct data_template* private_data, 
    int op_idx
);

#endif
