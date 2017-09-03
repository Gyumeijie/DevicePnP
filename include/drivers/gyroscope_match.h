#ifndef GYROSCOPE_MATCH_H
#define GYROSCOPE_MATCH_H

#include "driver_match.h"
#include "gyroscope.h"

//支持不同接口的定义不同模板
#define GYROSCOPE_TEMPLATE_NUM 10
#define MATCH_FUNCS_NUM  6

#define REQUIRED_OPS  \
           ((1<<GYROSCOPE_GLOBAL_INDEX) | (1<<GYROSCOPE_OPEN_INDEX))
           
#define  REQUIRED_OP_NUM  2
static unsigned int required_ops_index[REQUIRED_OP_NUM] = {GYROSCOPE_GLOBAL_INDEX, GYROSCOPE_OPEN_INDEX};
static const char* required_ops_name[REQUIRED_OP_NUM] = {"global", "open"};

static struct min_function_set gyro_mfs = {
   REQUIRED_OPS,
   REQUIRED_OP_NUM,
   required_ops_index,
   required_ops_name
};




//模板参数结构体表
//static struct template_data* template_data_table;

//具体模板参数结构体
struct gyroscope_global{
  unsigned char slave_address;
};


static struct gyroscope_global* gyro_globalp;

static struct struct_member gyro_global[1] = {
   {"char","slave_address", 0},
};

struct get_reg_pattern0{
    unsigned char reg_address;
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

static int global_match(void);
static void gyro_global_do_fill(int index, void* data);

//open相关的模板匹配函数
static int open_template0_match(void);

//getx相关的模板匹配函数
static int getx_template0_match(void);
static int gety_template0_match(void);
static int getz_template0_match(void);
static int getxyz_template0_match(void);

static int has_all_required_ops_complemented(void);
extern int gyroscope_match(void);

#endif

