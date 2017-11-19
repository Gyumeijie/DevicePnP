#include "driver_supported_interface.h"
#include <string.h>
#include <stdio.h>

Boolean is_supported_interface
(
    interface_t* driver_supported_interfaces, 
    char* device_interface
)
{
    char* result = strstr(driver_supported_interfaces->interfaces_string,
                          device_interface);

    return result == NULL ? False : True;
}


int add_supported_interface
(
    interface_t* driver_supported_interfaces, 
    const char* interface
)
{ 
    //一般情况下32个字符已经足够了，所以这里就不需要添加长度是否够用的检查
    char* interfaces_string;
    int last_pos;

    last_pos = driver_supported_interfaces->last_pos;
    interfaces_string = (char*)driver_supported_interfaces->interfaces_string;
   
    strcpy(&interfaces_string[last_pos], interface);
    driver_supported_interfaces->last_pos += strlen(interface);
    
    return 0;
}

