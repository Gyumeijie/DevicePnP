#ifndef MAGNETORQUER_DRIVER_H
#define MAGNETORQUER_DRIVER_H

#include "magnetorquer_match.h"

static void general_magnetorquer_open(void* private_data);

static int set_pattern0(void* para_struct, unsigned int* data);

static int general_magnetorquer_setx(void* private_data, unsigned int* data);
static int magnetorquer_setx_template0(void* para_struct, unsigned int* data);

static int general_magnetorquer_sety(void* private_data, unsigned int* data);
static int magnetorquer_sety_template0(void* para_struct, unsigned int* data);


static int general_magnetorquer_setz(void* private_data, unsigned int* data);
static int magnetorquer_setz_template0(void* para_struct, unsigned int* data);


static int general_magnetorquer_setxyz(void* private_data, unsigned int* data);
static int magnetorquer_setxyz_template0(void* para_struct, unsigned int* data);

static void fetch_data(void* private_data, int op_idx);

extern void magnetorquer_driver_loader(void);

#endif
