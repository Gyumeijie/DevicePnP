#ifndef DRIVER_SUPPORTED_INTERFACE_H
#define DRIVER_SUPPORTED_INTERFACE_H

//TODO 可以移到全局的可配置项
#define MAX_INTERFACE_STRING_LENGTH 32
#include "types.h"

// last_pos成员的初始化值需为0，客户代码可以通过声明static或
// 者利用下面的方式进行初始化：interface_t var = {0}，但比较推
// 荐使用第一种方法，这样能更好地隐藏其内部的实现以及当内部实现细节
// 改变时减少对客户代码破坏
typedef struct{
   char interfaces_string[MAX_INTERFACE_STRING_LENGTH];
   int last_pos;
}interface_t;


extern Boolean is_supported_interface
(
    interface_t* driver_supported_interfaces, 
    char* device_interface
);

extern int add_supported_interface
(
    interface_t* driver_supported_interfaces, 
    const char* interface
);

#endif
