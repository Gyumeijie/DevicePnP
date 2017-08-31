#ifndef GYROSCOPE_DRIVER_H
#define GYROSCOPE_DRIVER_H


#include "gyroscope_match.h"


static void gyroscope_open(void* private_data);

static void gyroscope_open_template0(void* para_struct);

static void gyroscope_getx(void* private_data, unsigned int data[]);

static void gyroscope_getx_template0(void* para_struct, unsigned int data[]);

extern void gyroscope_driver_loader(void);

#endif 
