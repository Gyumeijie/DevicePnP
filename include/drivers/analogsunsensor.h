#ifndef ANALOGSUNSENSOR_H
#define ANALOGSUNSENSOR_H

#define ANALOGSUNSENSOR_GLOBAL_INDEX 0
#define ANALOGSUNSENSOR_OPEN_INDEX 1
#define ANALOGSUNSENSOR_READ_INDEX 2

#define ANALOGSUNSENSOR_OP_NUM 2

struct analogsunsensor_device_operation{
    int (*general_analogsunsensor_open)(void*, void*);
    int (*general_analogsunsensor_read)(void*, void*);
};

extern  int analogsunsensor_open(char* lid);
extern  int analogsunsensor_read(int index, void* data);

#endif
