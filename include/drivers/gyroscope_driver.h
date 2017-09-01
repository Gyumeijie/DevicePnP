#ifndef GYROSCOPE_DRIVER_H
#define GYROSCOPE_DRIVER_H


#include "gyroscope_match.h"


static void general_gyroscope_open(void* private_data);

static void gyroscope_open_template0(void* para_struct);

static int get_pattern0(void* para_struct, unsigned int* data);

static int general_gyroscope_getx(void* private_data, unsigned int* data);
static int gyroscope_getx_template0(void* para_struct, unsigned int* data);

static int general_gyroscope_gety(void* private_data, unsigned int* data);
static int gyroscope_gety_template0(void* para_struct, unsigned int* data);

static int general_gyroscope_getz(void* private_data, unsigned int* data);
static int gyroscope_getz_template0(void* para_struct, unsigned int* data);

static int general_gyroscope_getxyz(void* private_data, unsigned int* data);
static int gyroscope_getxyz_template0(void* para_struct, unsigned int* data);

static void fetch_data(void* private_data, int index);

extern void gyroscope_driver_loader(void);

#endif 
