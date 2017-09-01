#include "device_open.h"
#include "analogsunsensor.h"
#include "analogsunsensor_common.h"
#include "analogsunsensor_match.h"
#include <stdio.h>

static struct device_open* devop = NULL;
static struct analogsunsensor_device_operation* adop = NULL;

int analogsunsensor_open(char* lid)
{
    int index;
    open_status os;

    index = open_device(lid, &os);
    //如果打开失败
    if (index == -1) return -1;
    //如果已经打开
    if(os == ALREADY_OPEN) return index;

    devop = get_device_open_struct(index);
    if (has_op_complemented(devop->private_data, ANALOGSUNSENSOR_OPEN_INDEX)){
    adop = devop->device_operation;    
    adop->general_analogsunsensor_open(devop->private_data);
    }

    return index;
}


int analogsunsensor_read(int index, unsigned int* data)
{
    int result = -1;
    devop = get_device_open_struct(index);
    adop = devop->device_operation;
    
    if(has_op_complemented(devop->private_data, ANALOGSUNSENSOR_READ_INDEX)){
        result = adop->general_analogsunsensor_read(devop->private_data, data);
    }else{
        printf("analogsunsensor_read not implemented\n");
    }

    return result;
}


