#include "driver.h"
#include "driver_loaders.h"
#include "driver_register.h"
#include <string.h>
#include <malloc.h>
#include <stdio.h>

void register_drivers(void)
{
    int i;
    unsigned int driver_loader_num = get_driver_loader_num();
    for (i=0; i<driver_loader_num; i++){
        // 依次获取驱动加载函数
        driver_loader loader = get_driver_loader();

        // 执行驱动加载函数，由其将设备驱动结构体注册到设备驱动索引表中
        loader();
    }
}
