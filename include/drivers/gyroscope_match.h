#ifndef GYROSCOPE_MATCH_H
#define GYROSCOPE_MATCH_H

#include "driver_match.h"


//支持不同接口的定义不同模板
#define GYROSCOPE_TEMPLATE_NUM 10

//定义gyroscope提供的操作
#define GYROSCOPE_OP_NUM 6

//
#define GYROSCOPE_GLOBAL_INDEX 0
#define GYROSCOPE_OPEN_INDEX 1
#define GYROSCOPE_GETX_INDEX 2
#define GYROSCOPE_GETY_INDEX 3
#define GYROSCOPE_GETZ_INDEX 4
#define GYROSCOPE_GETXYZ_INDEX 5

//模板参数结构体表
//static struct template_data* template_data_table;
static struct match_info* mip;

//具体模板参数结构体
#if 0
struct global{
    char slave_address;
};
static struct global* gyro_global;
#endif

struct get_reg_pattern0{
    char reg_address;
    int size;
};
static struct get_reg_pattern0* getreg_pat0p;

static struct struct_member getreg_pat0[2] = {
       {"char", "reg_address", 0},
       {"int", "size", 1}
};

#if 0
struct getx_template0{
    char reg_address;
    int size;
};
static struct getx_template0* getx_tpl0p;
#endif 

static int getreg_pat0_match(char* op_name, char* para_name, int index);
static void getreg_pat0_do_fill(int index, void* data);

//open相关的模板匹配函数
static int open_template0_match(void);

//getx相关的模板匹配函数
static int getx_template0_match(void);
static int gety_template0_match(void);
static int getz_template0_match(void);
static int getxyz_template0_match(void);

extern int gyroscope_match(void);

#endif

