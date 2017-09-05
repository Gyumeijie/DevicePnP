#ifndef DRIVER_MATCH_H
#define DRIVER_MATCH_H

#define MATCH 1
#define UNMATCH 0

#define MAX_TEMPLATE_NAME_LENGTH 64

//定义填充结构体的函数类型
typedef void (*struct_fill_func_ptr)(int, void*);

//定义模板匹配函数类型
typedef int (*match_func_ptr) (void);

//定义寄存器结构
struct reg{
  char addr;
  char val;
};

//定义收集设备配置文件中类型为reg_array的para_list的结构体
struct reg_array{
    int len; 
    struct reg* regp;
};


//定义收集设备配置文件中类型为plain_array的para_list的结构体
struct plain_array{
    int len;
    void* arr;
    char* type;
};

//定义收集设备配置文件中类型为struct的para_list的结构体
struct struct_member{
    char* type;
    char* name;
    int index;
};

//定义模板匹配结构体
struct template_match{
    char* name;
    match_func_ptr match_func;
};

//定义描述设备驱动的最小功能集结构体
struct min_function_set{
  int required_ops;
  int required_ops_num;
  int* required_ops_index;
  const char** required_ops_name;
};


//定义模板参数结构体
struct template_data{
    int template_id;
    void* para_struct;
};

//匹配信息结构体
struct match_info{
 int data_table_size;
 struct template_match* match_funcs_table;
 int match_funcs_num;
 struct min_function_set* mfsp;
 int* complementation_record;
};

static struct match_info* g_mip; 

static struct template_data* template_data_table;

static int find_and_exec_match_func(char* name);

static void undo_match(void);

static void init_template_data_table(int dtsize);

static match_func_ptr find_match_func(char* name);

static void 
construct_template_name(char* template_name, char* op_name, int template_id);

static int try_match(char* template_name);

static int has_all_required_ops_complemented(void);

extern int check_match(int status, int index, int template_id, void* template_data);

extern int do_match(struct match_info* mip); 

extern void* get_template_data_table(void);

extern const char* get_op_context();

extern int has_op_complemented(struct template_data* private_data, int op_idx);

#endif
