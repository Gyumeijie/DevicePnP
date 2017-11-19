#ifndef ANALOGSUNSENSOR_DRIVER_H
#define ANALOGSUNSENSOR_DRIVER_H

#include "driver_operation_function.h"
#include "analogsunsensor_match.h"
#include "analogsunsensor_open.h"
#include "analogsunsensor_read.h"

static int general_analogsunsensor_open(void* private_data, void* data);

static int general_analogsunsensor_read(void* private_data, void* data);

static void fetch_data(void* private_data, int op_idx);

extern void analogsunsensor_driver_loader(void);

static driver_operation_function analogsunsensor_open_templates[] = {
   analogsunsensor_open_template0,    
};


static driver_operation_function analogsunsensor_read_templates[] = {
   analogsunsensor_read_template0,    
};

#endif
