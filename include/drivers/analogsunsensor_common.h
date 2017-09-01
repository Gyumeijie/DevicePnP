#ifndef ANALOGSUNSENSOR_COMMON_H
#define ANALOGSUNSENSOR_COMMON_H

struct analogsunsensor_device_operation{
    void (*general_analogsunsensor_open)(void*);
    int (*general_analogsunsensor_read)(void*, unsigned int*);
};

#endif
