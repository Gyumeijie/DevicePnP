#ifndef GYROSCOPE_H
#define GYROSCOPE_H


//定义gyroscope提供的操作
#define GYROSCOPE_OP_NUM 6

#define GYROSCOPE_GLOBAL_INDEX 0
#define GYROSCOPE_OPEN_INDEX 1
#define GYROSCOPE_GETX_INDEX 2
#define GYROSCOPE_GETY_INDEX 3
#define GYROSCOPE_GETZ_INDEX 4
#define GYROSCOPE_GETXYZ_INDEX 5

struct gyroscope_device_operation{
 void (*general_gyroscope_open)(void*);
 int (*general_gyroscope_getx)(void*, unsigned int*);
 int (*general_gyroscope_gety)(void*, unsigned int*);
 int (*general_gyroscope_getz)(void*, unsigned int*);
 int (*general_gyroscope_getxyz)(void*, unsigned int*);
};

extern int gyroscope_open(char* lid);

extern int gyroscope_getx(int index, unsigned int* data);

extern int gyroscope_gety(int index, unsigned int* data);

extern int gyroscope_getz(int index, unsigned int* data);

extern int gyroscope_getxyz(int index, unsigned int* data);

static int gyroscope_get_helpler(int dev_open_idx, int op_idx, 
                                 const char* func_name, unsigned int * data);

#endif
