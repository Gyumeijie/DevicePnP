#ifndef GYROSCOPE_DRIVER_H
#define GYROSCOPE_DRIVER_H


#include "driver_operation_function.h"
#include "gyroscope_match.h"
#include "gyroscope_open.h"
#include "gyroscope_getx.h"
#include "gyroscope_gety.h"
#include "gyroscope_getz.h"
#include "gyroscope_getxyz.h"


static int general_gyroscope_open(void* private_data, void* data);

static int get_pattern0(void* para_struct, void* data);

static int general_gyroscope_getx(void* private_data, void* data);

static int general_gyroscope_gety(void* private_data, void* data);

static int general_gyroscope_getz(void* private_data, void* data);

static int general_gyroscope_getxyz(void* private_data, void* data);

static void fetch_data(void* private_data, int index);

extern void gyroscope_driver_loader(void);


static driver_operation_function gyroscope_open_templates[] = {
   gyroscope_open_template0,    
};

static driver_operation_function gyroscope_getx_templates[] = {
   gyroscope_getx_template0,    
};


static driver_operation_function gyroscope_gety_templates[] = {
   gyroscope_gety_template0,    
};


static driver_operation_function gyroscope_getz_templates[] = {
   gyroscope_getz_template0,    
};


static driver_operation_function gyroscope_getxyz_templates[] = {
   gyroscope_getxyz_template0,    
};

#endif 
