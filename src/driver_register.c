#include "driver.h"
#include "driver_loaders.h"
#include "driver_register.h"
#include <string.h>
#include <malloc.h>
#include <stdio.h>

/**
 * 输入：无
 * 输出：无
 * 功能：注册驱动
 */
void register_drivers(void)
{
    unsigned int driver_loader_num;
    driver_loader loader;
    int i;


#if DEBUG
    printf("\n---------------Begin driver registeration-----------------\n\n");
#endif

    driver_loader_num = get_driver_loader_num();
    for (i=0; i<driver_loader_num; i++){
        //依次获取驱动加载函数
        loader = get_driver_loader();
        //执行驱动加载函数，由其将设备驱动结构体注册到设备驱动索引表中
        loader();
    }

#if DEBUG
    printf("driver loaders num: %d\n", driver_loader_num);
    printf("\n------------------End driver registeration------------------\n");
#endif
}



