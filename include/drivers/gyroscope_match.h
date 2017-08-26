#ifndef GYROSCOPE_MATCH_H
#define GYROSCOPE_MATCH_H

#include "driver_match.h"


//支持不同接口的定义不同模板
#define GYROSCOPE_TEMPLATE_NUM 10

//定义gyroscope提供的操作
#define GYROSCOPE_OP_NUM 5

//
#define GYROSCOPE_GLOBAL_INDEX 0
#define GYROSCOPE_OPEN_INDEX 1
#define GYROSCOPE_GETX_INDEX 2

//模板参数结构体表
static struct template_data* template_data_table;


//具体模板参数结构体
#if 0
struct global{
    char slave_address;
};
static struct global* gyro_global;
#endif

static struct reg_array* open_template0;

struct getx_template0{
    char reg_address;
    int size;
};
static struct getx_template0* getx_tpl0p;


//open相关的模板匹配函数
static int open_template0_match(void);

//getx相关的模板匹配函数
static int getx_template0_match(void);
static void getxtpl0_do_fill(int index, void* data);

static int find_and_exec_match_func(char* name);

static void undo_match(void);

static void* init_template_data_table(void);

static match_func_ptr find_match_func(char* name);

static int check_match(int status, int index, int template_id, void* template_data);

extern int gyroscope_match(void);

#endif

