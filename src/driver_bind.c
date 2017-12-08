#include "device.h"
#include "driver.h"
#include "driver_bind.h"
#include "driver_match.h"
#include "config_info_collect.h"
#include "error_report.h"
#include <stdio.h>

int bind_drivers(void)
{

    int i;
    unsigned int device_num = get_device_num();
    for (i=0; i<device_num; i++){
        struct device* devp = get_device();
        devno_t devno = devp->devno;

        // 根据设备接口类型获取设备驱动索引表中的相应驱动结构体
        struct driver* drip = get_driver(GET_MAJOR(devno), devp->interface);
        if (! check_null(__FILE__, __func__, "drip", drip)){
            printf("Detail: can't not find driver for %s of %s\n", 
                              major2type(GET_MAJOR(devno)), devp->interface);
            continue;
        }

        // 如果配置文件中没有lid对应的配置信息
        if (! establish_device_context(devp->lid)){
            destroy_device_context();
            return FAILURE;
        }

        // 调用通用驱动提供的match函数并判断匹配的结果
        int exec_status = drip->match();
        if (exec_status){
            do_bind(devp, drip);
        } else {
            destroy_device_context();
            return FAILURE;
        }

        destroy_device_context();

   }

    release_drivers();

    return SUCCESS;
}


static void do_bind(struct device* devp, struct driver* drip)
{
    devp->device_operation = drip->device_operation;
    devp->private_data = get_template_data_table();
}



