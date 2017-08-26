#ifndef ANALOGSUNSENSOR_DRIVER_H
#define ANALOGSUNSENSOR_DRIVER_H

#include "analogsunsensor_match.h"

//static int analogsunsensor_match(void);

static void analogsunsensor_open(void* private_data);
static void analogsunsensor_open_template0(void* para_struct);

static void analogsunsensor_read(void* private_data);
static void analogsunsensor_read_template0(void* para_struct);

extern void analogsunsensor_driver_loader(void);
#endif
