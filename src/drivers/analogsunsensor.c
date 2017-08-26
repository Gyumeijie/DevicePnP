#include "device_open.h"
#include "analogsunsensor.h"
#include "analogsunsensor_common.h"
#include "analogsunsensor_match.h"
#include <stdio.h>

static struct device_open* devop = NULL;
static struct analogsunsensor_device_operation* adop = NULL;
static void* para_struct = NULL;

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
    adop = devop->device_operation;    
    adop->general_analogsunsensor_open(devop->private_data);

    return index;
}

void analogsunsensor_read(int index)
{
    devop = get_device_open_struct(index);
    adop = devop->device_operation;
    //需要根据匹配情况，判断该操作是否有配置
    para_struct = ((struct template_data*)devop->private_data)[ANALOGSUNSENSOR_READ_INDEX].para_struct;
    
    if(para_struct != NULL){
        adop->general_analogsunsensor_read(devop->private_data);
    }
#if DEBUG
    else{
       printf("analogsunsensor_getx not implemented\n");
      }
#endif 
}


