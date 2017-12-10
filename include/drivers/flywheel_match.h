#ifndef FLYWHEEL_MATCH_H
#define FLYWHEEL_MATCH_H

#include "driver_match.h"

#define FLYWHEEL_TEMPLATE_NUM 10
#define MATCH_FUNCS_NUM  4

static int global_match_template0(void);

static int open_match_template0(void);

static int set_speed_match_template0(void);

static int receive_match_template0(void);

extern int flywheel_match(void);

#endif
