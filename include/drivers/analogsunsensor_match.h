#ifndef ANALOGSUNSENSOR_MATCH_H
#define ANALOGSUNSENSOR_MATCH_H

#include "driver_match.h"

#define ANALOGSUNSENSOR_TEMPLATE_NUM 10

#define ANALOGSUNSENSOR_OP_NUM 2

#define ANALOGSUNSENSOR_GLOBAL_INDEX 0
#define ANALOGSUNSENSOR_OPEN_INDEX 1
#define ANALOGSUNSENSOR_READ_INDEX 2

//模板参数结构体表
static struct template_data* template_data_table;

static struct plain_array* read_template0;

//open相关的模板匹配函数
static int open_template0_match(void);

//read相关的模板匹配函数
static int read_template0_match(void);

extern int analogsunsensor_match(void);
#endif
