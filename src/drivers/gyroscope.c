#include "device_open.h"
#include "gyroscope.h"
#include "gyroscope_common.h"
#include "gyroscope_match.h"
#include <stdio.h>

static struct device_open* devop = NULL;
static struct gyroscope_device_operation* gdop = NULL;
static void* para_struct = NULL;

int gyroscope_open(char* lid)
{
    int index;
    open_status os;

    index = open_device(lid, &os);
    //如果打开失败
    if (index == -1) return -1;
    //如果已经打开
    if(os == ALREADY_OPEN) return index;

    devop = get_device_open_struct(index);
    gdop = devop->device_operation;    
    gdop->general_gyroscope_open(devop->private_data);

    return index;
}

void gyroscope_getx(int index, unsigned int* data)
{
    devop = get_device_open_struct(index);
    gdop = devop->device_operation;
    //需要根据匹配情况，判断该操作是否有配置
    para_struct = ((struct template_data*)devop->private_data)[GYROSCOPE_GETX_INDEX].para_struct;
    
    if(para_struct != NULL){
        gdop->general_gyroscope_getx(devop->private_data, data);
    }
#if DEBUG
    else{
       printf("gyroscope_getx not implemented\n");
      }
#endif 
}


