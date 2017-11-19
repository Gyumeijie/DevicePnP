#ifndef FLYWHEEL_DRIVER_H
#define FLYWHEEL_DRIVER_H

#include "driver_operation_function.h"
#include "flywheel_match.h"
#include "flywheel_open.h"
#include "flywheel_set_speed.h"
#include "flywheel_receive.h"


static int general_flywheel_open(void* private_data, void* para);

static int general_flywheel_set_speed(void* private_data, void* para);

static int general_flywheel_receive(void* private_data, void* para);

static void fetch_data(void* private_data, int op_idx);

extern void flywheel_driver_loader(void);

typedef int (*driver_operation_function)(void*, void*);


static driver_operation_function flywheel_open_templates[] = {
   flywheel_open_template0,
};

static driver_operation_function flywheel_set_speed_templates[] = {
   flywheel_set_speed_template0, 
};

static driver_operation_function flywheel_receive_templates[] = {
   flywheel_receive_template0, 
};

#endif
