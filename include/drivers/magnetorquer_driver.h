#ifndef MAGNETORQUER_DRIVER_H
#define MAGNETORQUER_DRIVER_H

#include "driver_operation_function.h"
#include "magnetorquer_match.h"
#include "magnetorquer_open.h"
#include "magnetorquer_setx.h"
#include "magnetorquer_sety.h"
#include "magnetorquer_setz.h"
#include "magnetorquer_setxyz.h"

static int general_magnetorquer_open(void* private_data, void*);

static int general_magnetorquer_setx(void* private_data, void* data);

static int general_magnetorquer_sety(void* private_data, void* data);

static int general_magnetorquer_setz(void* private_data, void* data);

static int general_magnetorquer_setxyz(void* private_data, void* data);

static void fetch_data(void* private_data, int op_idx);

extern void magnetorquer_driver_loader(void);


static driver_operation_function magnetorquer_open_templates[] = {
   magnetorquer_open_template0,    
};

static driver_operation_function magnetorquer_setx_templates[] = {
   magnetorquer_setx_template0,    
};

static driver_operation_function magnetorquer_sety_templates[] = {
   magnetorquer_sety_template0,    
};

static driver_operation_function magnetorquer_setz_templates[] = {
   magnetorquer_setz_template0,    
};

static driver_operation_function magnetorquer_setxyz_templates[] = {
   magnetorquer_setxyz_template0,    
};

#endif

