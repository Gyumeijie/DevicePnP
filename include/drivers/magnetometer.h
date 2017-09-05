#ifndef MAGNETOMETER_H
#define MAGNETOMETER_H

#define MAGNETOMETER_GLOBAL_INDEX 0
#define MAGNETOMETER_OPEN_INDEX 1
#define MAGNETOMETER_GETX_INDEX 2
#define MAGNETOMETER_GETY_INDEX 3
#define MAGNETOMETER_GETZ_INDEX 4
#define MAGNETOMETER_GETXYZ_INDEX 5

#define MAGNETOMETER_OP_NUM 5

struct magnetometer_device_operation{
    void (*general_magnetometer_open)(void*);
    int (*general_magnetometer_getx)(void*, unsigned int*);
    int (*general_magnetometer_gety)(void*, unsigned int*);
    int (*general_magnetometer_getz)(void*, unsigned int*);
    int (*general_magnetometer_getxyz)(void*, unsigned int*);
};

static int magnetometer_get_helper(int dev_open_idx, int op_idx, 
                                   const char* func_name, unsigned int* data);
extern  int magnetometer_open(char* lid);
extern  int magnetometer_getx(int index, unsigned int* data);
extern  int magnetometer_gety(int index, unsigned int* data);
extern  int magnetometer_getz(int index, unsigned int* data);
extern  int magnetometer_getxyz(int index, unsigned int* data);

#endif
