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
    get_para_struct(index, GYROSCOPE_GETX_INDEX);
    (para_struct == NULL) 
       ? puts("gyroscope_getx not implemented\n")
       : gdop->general_gyroscope_getx(devop->private_data, data); 
}


void gyroscope_gety(int index, unsigned int* data)
{
    get_para_struct(index, GYROSCOPE_GETY_INDEX);
    (para_struct == NULL)
       ? puts("gyroscope_gety not implemented\n")
       : gdop->general_gyroscope_gety(devop->private_data, data); 
}


void gyroscope_getz(int index, unsigned int* data)
{
    get_para_struct(index, GYROSCOPE_GETZ_INDEX);
    
    (para_struct == NULL)
       ? puts("gyroscope_getz not implemented\n")
       : gdop->general_gyroscope_getz(devop->private_data, data); 
}


void gyroscope_getxyz(int index, unsigned int* data)
{
    get_para_struct(index, GYROSCOPE_GETXYZ_INDEX); 
    (para_struct == NULL)
       ? puts("gyroscope_getxyz not implemented\n")
       : gdop->general_gyroscope_getxyz(devop->private_data, data); 
}


static void* get_para_struct(int dev_open_idx, int op_idx)
{
    devop = get_device_open_struct(dev_open_idx);
    gdop = devop->device_operation;
    //需要根据匹配情况，判断该操作是否有配置
    para_struct = ((struct template_data*)devop->private_data)[op_idx].para_struct;
}
