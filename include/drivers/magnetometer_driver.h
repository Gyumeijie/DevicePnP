#ifndef MAGNETOMETER_DRIVER_H
#define MAGNETOMETER_DRIVER_H

#include "driver_operation_function.h"
#include "magnetometer_match.h"
#include "magnetometer_open.h"
#include "magnetometer_getx.h"
#include "magnetometer_gety.h"
#include "magnetometer_getz.h"
#include "magnetometer_getxyz.h"

static int general_magnetometer_open(void* private_data, void* data);

static int general_magnetometer_getx(void* private_data, void* data);

static int general_magnetometer_gety(void* private_data, void* data);

static int general_magnetometer_getz(void* private_data, void* data);

static int general_magnetometer_getxyz(void* private_data, void* data);

static void fetch_data(void* private_data, int op_idx);

extern void magnetometer_driver_loader(void);


static driver_operation_function magnetometer_open_templates[] = {
   magnetometer_open_template0,    
};


static driver_operation_function magnetometer_getx_templates[] = {
   magnetometer_getx_template0,    
};


static driver_operation_function magnetometer_gety_templates[] = {
   magnetometer_gety_template0,    
};


static driver_operation_function magnetometer_getz_templates[] = {
   magnetometer_getz_template0,    
};


static driver_operation_function magnetometer_getxyz_templates[] = {
   magnetometer_getxyz_template0,    
};

#endif
