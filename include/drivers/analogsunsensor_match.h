#ifndef ANALOGSUNSENSOR_MATCH_H
#define ANALOGSUNSENSOR_MATCH_H

#include "driver_match.h"

#define ANALOGSUNSENSOR_TEMPLATE_NUM 10
#define MATCH_FUNCS_NUM  3

//模板参数结构体表
static struct template_data* template_data_table;

static struct plain_array* read_template0;

static int global_match(void);

//open相关的模板匹配函数
static int open_template0_match(void);

//read相关的模板匹配函数
static int read_template0_match(void);

extern int analogsunsensor_match(void);

#endif
