#ifndef ANALOGSUNSENSOR_DRIVER_H
#define ANALOGSUNSENSOR_DRIVER_H

#include "analogsunsensor_match.h"

static void analogsunsensor_open(void* private_data);

static int analogsunsensor_read(void* private_data, unsigned int* data);
static int analogsunsensor_read_template0(void* para_struct, unsigned int* data);

static void fetch_data(void* private_data, int index);

extern void analogsunsensor_driver_loader(void);
#endif
