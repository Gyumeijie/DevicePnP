#ifndef MAGNETORQUER_MATCH_H
#define MAGNETORQUER_MATCH_H

#include "driver_match.h"

#define MAGNETORQUER_TEMPLATE_NUM 10
#define MATCH_FUNCS_NUM  6


static int global_match(void);

//open相关的模板匹配函数
static int open_template0_match(void);

static int set_pat0_match(int op_idx, char* op_name, char* para_name);

//set相关的模板匹配函数
static int setx_template0_match(void);
static int sety_template0_match(void);
static int setz_template0_match(void);
static int setxyz_template0_match(void);

extern int magnetorquer_match(void);

#endif
