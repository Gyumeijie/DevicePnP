#include "device_open.h"
#include "flywheel.h"
#include "flywheel_match.h"
#include "error_report.h"
#include "device.h"
#include <stdio.h>
#include <string.h>

static struct device* devp;
static struct flywheel_device_operation* fdop;

int flywheel_open(char* lid)
{
    open_status os;
    int index = open_device(lid, &os, "flywheel");

    // 如果打开失败
    if (index == -1) return -1;
    
    // 如果已经打开，则直接返回之前的索引号index
    if(os == ALREADY_OPEN) return index;
    
    devp = get_open_device(index);
    if (has_operation_complemented(devp->private_data,
                                   FLYWHEEL_OPEN_INDEX))
    {
       fdop = devp->device_operation;    
       fdop->general_flywheel_open(devp->private_data, NULL);
    }

    return index;
}


int flywheel_set_speed(int index, void* para)
{
    int result = -1;

    devp = get_open_device(index);
    assure_not_null(__FILE__, __func__, "devp", devp);
       
    // 检查使用flywheel_read的设备的类型是否为flywheel
    if (! check_device_type(devp, "flywheel")) return -1;
    
    fdop = devp->device_operation;
    if(has_operation_complemented(devp->private_data,
                                  FLYWHEEL_SET_SPEED_INDEX))
    {
        result = fdop->general_flywheel_set_speed(devp->private_data, para);
    }else{
        printf("flywheel_set_speed not implemented\n");
    }

    return result;
}


int flywheel_receive(int index, void* para)
{
    int result = -1;

    devp = get_open_device(index);
    assure_not_null(__FILE__, __func__, "devp", devp);
    
    // 检查使用flywheel_read的设备的类型是否为flywheel
    if (! check_device_type(devp, "flywheel")) return -1;
    
    fdop = devp->device_operation;
    if(has_operation_complemented(devp->private_data, 
                                  FLYWHEEL_SET_SPEED_INDEX))
    {
        //TODO 检查是否为空
        result = fdop->general_flywheel_receive(devp->private_data, para);
    }else{
        printf("flywhee_receive not implemented\n");
    }

    return result;
}
