#include "device_open.h"
#include "flywheel.h"
#include "flywheel_match.h"
#include "error_report.h"
#include <stdio.h>
#include <string.h>

static struct device_open* devop;
static struct flywheel_device_operation* fdop;

int flywheel_open(char* lid)
{
    int index;
    open_status os;
    index = open_device(lid, &os, "flywheel");

    //如果打开失败
    if (index == -1) return -1;
    
    //如果已经打开，则直接返回之前的索引号index
    if(os == ALREADY_OPEN) return index;
    
    devop = get_device_open_struct(index);
    if (has_op_complemented(devop->private_data, FLYWHEEL_OPEN_INDEX)){
       fdop = devop->device_operation;    
       fdop->general_flywheel_open(devop->private_data, NULL);
    }

    return index;
}


int flywheel_set_speed(int index, void* para)
{
    int result = -1;

    devop = get_device_open_struct(index);
    if (!check_null(__FILE__, __func__, "devop", devop)){
       printf("Detail: can't find device open struct with index %d\n", index);
       return -1;
    }
    
    //检查使用flywheel_read的设备的类型是否为flywheel
    if (!check_device_type(devop, "flywheel")) return -1;
    
    fdop = devop->device_operation;
    if(has_op_complemented(devop->private_data, FLYWHEEL_SET_SPEED_INDEX)){
        result = fdop->general_flywheel_set_speed(devop->private_data, para);
    }else{
        printf("flywheel_set_speed not implemented\n");
    }

    return result;
}

int flywheel_receive(int index, void* para)
{
    int result = -1;

    devop = get_device_open_struct(index);
    if (!check_null(__FILE__, __func__, "devop", devop)){
       printf("Detail: can't find device open struct with index %d\n", index);
       return -1;
    }
    
    //检查使用flywheel_read的设备的类型是否为flywheel
    if (!check_device_type(devop, "flywheel")) return -1;
    
    fdop = devop->device_operation;
    if(has_op_complemented(devop->private_data, FLYWHEEL_SET_SPEED_INDEX)){
        //TODO 检查是否为空
        result = fdop->general_flywheel_receive(devop->private_data, para);
    }else{
        printf("flywhee_receive not implemented\n");
    }

    return result;
}
