#ifndef MAGNETOMETER_MATCH_H
#define MAGNETOMETER_MATCH_H

#include "driver_match.h"

#define MAGNETOMETER_TEMPLATE_NUM 10
#define MATCH_FUNCS_NUM  6


static int global_match(void);

//open相关的模板匹配函数
static int open_template0_match(void);

static int get_pat0_match(int op_idx, char* op_name, char* para_name);

//get相关的模板匹配函数
static int getx_template0_match(void);
static int gety_template0_match(void);
static int getz_template0_match(void);
static int getxyz_template0_match(void);

extern int magnetometer_match(void);

#endif
