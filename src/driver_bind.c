#include "device.h"
#include "driver.h"
#include "driver_bind.h"
#include "driver_match.h"
#include "config_info_collect.h"
#include "error_report.h"
#include <stdio.h>

int bind_drivers(void)
{
    struct device* devp = NULL;
    struct driver* drip = NULL;
    unsigned int device_num;
    devno_t devno;
    int exec_status;

    device_num = get_device_num();
   
    //依次处理设备索引表中的设备
    int i;
    for (i=0; i<device_num; i++){
        devp = get_device();
        devno = devp->devno;

        //根据设备接口类型获取设备驱动索引表中的相应驱动结构体
        drip = get_driver(GET_MAJOR(devno), devp->interface);
        if(!check_null(__FILE__, __func__, "drip", drip)){
            printf("Detail: can't not find driver for %s of %s\n", 
                              major2type(GET_MAJOR(devno)), devp->interface);
            continue;
        }

       //如果配置文件中没有lid对应的配置信息
        if (!establish_device_context(devp->lid)){
            destroy_device_context();
            return FAILURE;
        }

       //调用通用驱动提供的match函数并判断匹配的结果
        exec_status = drip->match();
        if (exec_status){
            do_bind(devp, drip);
        }else{
            destroy_device_context();
            return FAILURE;
        }

        destroy_device_context();

   }

    return SUCCESS;
}


static void do_bind(struct device* devp, struct driver* drip)
{
    devp->device_operation = drip->device_operation;
    devp->private_data = get_template_data_table();
}
