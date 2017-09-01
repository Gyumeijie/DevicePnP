#include "device_open.h"
#include "gyroscope.h"
#include "gyroscope_common.h"
#include "gyroscope_match.h"
#include <stdio.h>

static struct device_open* devop = NULL;
static struct gyroscope_device_operation* gdop = NULL;

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
    if (has_op_complemented(devop->private_data, GYROSCOPE_OPEN_INDEX)){
        gdop = devop->device_operation;
        gdop->general_gyroscope_open(devop->private_data);
    }

    return index;
}

int gyroscope_getx(int index, unsigned int* data)
{
    return gyroscope_get_helpler(index, GYROSCOPE_GETX_INDEX, __func__, data);
}


int gyroscope_gety(int index, unsigned int* data)
{
    return gyroscope_get_helpler(index, GYROSCOPE_GETY_INDEX, __func__, data);
}


int gyroscope_getz(int index, unsigned int* data)
{
    return gyroscope_get_helpler(index, GYROSCOPE_GETZ_INDEX, __func__, data);
}


int gyroscope_getxyz(int index, unsigned int* data)
{
    return gyroscope_get_helpler(index, GYROSCOPE_GETXYZ_INDEX, __func__, data);
}


static int gyroscope_get_helpler(int dev_open_idx, int op_idx, const char* func_name, unsigned int * data)
{
    int result = -1;
 
    devop = get_device_open_struct(dev_open_idx); 
    gdop = devop->device_operation;

    if (has_op_complemented(devop->private_data, op_idx)){
         switch (op_idx){
               case GYROSCOPE_GETX_INDEX: 
                    result =  gdop->general_gyroscope_getx(devop->private_data, data); 
                    break;
               case GYROSCOPE_GETY_INDEX: 
                    result =  gdop->general_gyroscope_gety(devop->private_data, data); 
                    break;
               case GYROSCOPE_GETZ_INDEX: 
                    result =  gdop->general_gyroscope_getz(devop->private_data, data); 
                    break;
               case GYROSCOPE_GETXYZ_INDEX: 
                    result =  gdop->general_gyroscope_getxyz(devop->private_data, data); 
                    break;
               default:
                    break;
         }
    }else{

	printf("%s not configured in xml file\n", func_name);
    }

    return result;
}
