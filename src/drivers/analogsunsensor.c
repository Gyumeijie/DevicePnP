#include "device_open.h"
#include "analogsunsensor.h"
#include "analogsunsensor_match.h"
#include "error_report.h"
#include "device.h"
#include <stdio.h>
#include <string.h>

static struct device* devp;
static struct analogsunsensor_device_operation* adop;

int analogsunsensor_open(char* lid)
{
    open_status os;
    int index = open_device(lid, &os, "analogsunsensor");
   
    // 如果打开失败
    if (index == -1) return -1;
    
    // 如果已经打开，则直接返回之前的索引号index
    if(os == ALREADY_OPEN) return index;
    
    devp = get_open_device(index);
    if (has_operation_complemented(devp->private_data, 
                                   ANALOGSUNSENSOR_OPEN_INDEX))
    {
       adop = devp->device_operation;    
       adop->general_analogsunsensor_open(devp->private_data, NULL);
    }

    return index;
}


int analogsunsensor_read(int index, void* data)
{
    int result = -1;

    devp = get_open_device(index);
    if (! check_null(__FILE__, __func__, "devp", devp)){
       printf("Detail: can't find device open struct with index %d\n", index); 
       return -1;
    }
    
    // 检查使用analogsunsensor_read的设备的类型是否为analogsunsensor
    if (! check_device_type(devp, "analogsunsensor")) return -1;
    
    adop = devp->device_operation;
    if(has_operation_complemented(devp->private_data, 
                                  ANALOGSUNSENSOR_READ_INDEX))
    {
        result = adop->general_analogsunsensor_read(devp->private_data, data);
    }else{
        printf("analogsunsensor_read not implemented\n");
    }

    return result;
}

