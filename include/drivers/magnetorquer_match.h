#ifndef MAGNETORQUER_MATCH_H
#define MAGNETORQUER_MATCH_H

#include "driver_match.h"

#define MAGNETORQUER_TEMPLATE_NUM 10
#define MATCH_FUNCS_NUM  6

static int global_match(void);

static int open_match_template0(void);

static int set_pat0_match(char* op_name, char* para_name, int op_idx);

static int setx_match_template0(void);
static int sety_match_template0(void);
static int setz_match_template0(void);
static int setxyz_match_template0(void);

extern int magnetorquer_match(void);

#endif
