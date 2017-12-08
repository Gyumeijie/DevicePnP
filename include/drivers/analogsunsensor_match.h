#ifndef ANALOGSUNSENSOR_MATCH_H
#define ANALOGSUNSENSOR_MATCH_H

#include "driver_match.h"

#define ANALOGSUNSENSOR_TEMPLATE_NUM 10
#define MATCH_FUNCS_NUM  3


static int global_match_template0(void);

static int open_match_template0(void);

static int read_match_template0(void);

extern int analogsunsensor_match(void);

#endif
