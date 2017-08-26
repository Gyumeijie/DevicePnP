#ifndef DRIVER_MATCH_H
#define DRIVER_MATCH_H


#define MAX_TEMPLATE_NAME_LENGTH 64

//定义填充结构体的函数类型
typedef void (*fill_struct)(int, void*);

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
};

//定义收集设备配置文件中类型为struct的para_list的结构体
struct st_member{
    char* type;
    char* name;
    int index;
};

//定义模板匹配结构体
struct template_match{
    char* name;
    match_func_ptr match_func;
};



#if 0
//定义模板匹配函数结构体表
struct match_func_table{
     int size;
     struct template_match* match_funcs_array;
};
#endif 


//定义模板参数结构体
struct template_data{
    int template_id;
    void* para_struct;
};

static struct template_data* template_data_table;

extern int do_match(void* (*init_template_data_table)(void),
                    int (*find_and_exec_match_func)(char* func_name),
                    void (*undo_match)(void));

extern void* get_template_data_table(void);
#endif
