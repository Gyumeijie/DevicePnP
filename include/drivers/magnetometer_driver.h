#ifndef MAGNETOMETER_DRIVER_H
#define MAGNETOMETER_DRIVER_H

#include "magnetometer_match.h"

static void general_magnetometer_open(void* private_data);

static int get_pattern0(void* para_struct, unsigned int* data);

static int general_magnetometer_getx(void* private_data, unsigned int* data);
static int magnetometer_getx_template0(void* para_struct, unsigned int* data);

static int general_magnetometer_gety(void* private_data, unsigned int* data);
static int magnetometer_gety_template0(void* para_struct, unsigned int* data);


static int general_magnetometer_getz(void* private_data, unsigned int* data);
static int magnetometer_getz_template0(void* para_struct, unsigned int* data);


static int general_magnetometer_getxyz(void* private_data, unsigned int* data);
static int magnetometer_getxyz_template0(void* para_struct, unsigned int* data);

static void fetch_data(void* private_data, int op_idx);

extern void magnetometer_driver_loader(void);

#endif
