#ifndef MAGNETOMETER_MATCH_H
#define MAGNETOMETER_MATCH_H

#include "driver_match.h"

#define MAGNETOMETER_TEMPLATE_NUM 10
#define MATCH_FUNCS_NUM  6


static int global_match(void);

static int open_match_template0(void);

static int get_pat0_match(char* op_name, char* para_name, int op_idx);

static int getx_match_template0(void);
static int gety_match_template0(void);
static int getz_match_template0(void);
static int getxyz_match_template0(void);

extern int magnetometer_match(void);

#endif
