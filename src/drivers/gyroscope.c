#include "device_open.h"
#include "gyroscope.h"
#include "gyroscope_match.h"
#include "error_report.h"
#include <stdio.h>
#include <string.h>

static struct device_open* devop = NULL;
static struct gyroscope_device_operation* gdop = NULL;

int gyroscope_open(char* lid)
{
    int index;
    open_status os;

    index = open_device(lid, &os, "gyroscope");

    //如果打开失败
    if (index == -1) return -1;

    //如果已经打开，则直接返回之前的索引号index
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
    return gyroscope_get_helper(index, GYROSCOPE_GETX_INDEX, __func__, data);
}


int gyroscope_gety(int index, unsigned int* data)
{
    return gyroscope_get_helper(index, GYROSCOPE_GETY_INDEX, __func__, data);
}


int gyroscope_getz(int index, unsigned int* data)
{
    return gyroscope_get_helper(index, GYROSCOPE_GETZ_INDEX, __func__, data);
}


int gyroscope_getxyz(int index, unsigned int* data)
{
    return gyroscope_get_helper(index, GYROSCOPE_GETXYZ_INDEX, __func__, data);
}


static int gyroscope_get_helper(int dev_open_idx, int op_idx, 
                                 const char* func_name, unsigned int * data)
{
    int result = -1;
    void* private_data;

    devop = get_device_open_struct(dev_open_idx); 
    if (!check_null(__FILE__, __func__, "devop", devop)){
       printf("Detail: can't find device open struct with index %d\n",
                                                                 dev_open_idx);
       return -1;
    }
    
    //检查设备的类型是否为gyroscope
    if (!check_device_type(devop, "gyroscope")) return -1;

    gdop = devop->device_operation;
    private_data = devop->private_data;
    if (has_op_complemented(devop->private_data, op_idx)){
         switch (op_idx){
               case GYROSCOPE_GETX_INDEX: 
                    result =  gdop->general_gyroscope_getx(private_data, 
                                                           data); 
                    break;
               case GYROSCOPE_GETY_INDEX: 
                    result =  gdop->general_gyroscope_gety(private_data,
                                                           data); 
                    break;
               case GYROSCOPE_GETZ_INDEX: 
                    result =  gdop->general_gyroscope_getz(private_data,
                                                           data); 
                    break;
               case GYROSCOPE_GETXYZ_INDEX: 
                    result =  gdop->general_gyroscope_getxyz(private_data,
                                                             data); 
                    break;
               default:
                    break;
         }
    }else{
        char msg[128];
        sprintf(msg, "%s not configured in xml file", func_name);
        report_error(__FILE__, __func__, msg);
    }

    return result;
}
