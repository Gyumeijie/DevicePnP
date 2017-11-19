#include "device_open.h"
#include "analogsunsensor.h"
#include "analogsunsensor_match.h"
#include "error_report.h"
#include <stdio.h>
#include <string.h>

static struct device_open* devop;
static struct analogsunsensor_device_operation* adop;

int analogsunsensor_open(char* lid)
{
    int index;
    open_status os;

    index = open_device(lid, &os, "analogsunsensor");
   
    //如果打开失败
    if (index == -1) return -1;
    
    //如果已经打开，则直接返回之前的索引号index
    if(os == ALREADY_OPEN) return index;
    
    devop = get_device_open_struct(index);
    if (has_op_complemented(devop->private_data, ANALOGSUNSENSOR_OPEN_INDEX)){
       adop = devop->device_operation;    
       adop->general_analogsunsensor_open(devop->private_data, NULL);
    }

    return index;
}


int analogsunsensor_read(int index, void* data)
{
    int result = -1;

    devop = get_device_open_struct(index);
    if (!check_null(__FILE__, __func__, "devop", devop)){
       printf("Detail: can't find device open struct with index %d\n", index);
       return -1;
    }
    
    //检查使用analogsunsensor_read的设备的类型是否为analogsunsensor
    if (!check_device_type(devop, "analogsunsensor")) return -1;
    
    adop = devop->device_operation;
    if(has_op_complemented(devop->private_data, ANALOGSUNSENSOR_READ_INDEX)){
        result = adop->general_analogsunsensor_read(devop->private_data, data);
    }else{
        printf("analogsunsensor_read not implemented\n");
    }

    return result;
}

