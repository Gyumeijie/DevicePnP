#include "device_open.h"
#include "gyroscope.h"
#include "gyroscope_match.h"
#include "error_report.h"
#include "device.h"
#include <stdio.h>
#include <string.h>

static struct device* devp;
static struct gyroscope_device_operation* gdop;

int gyroscope_open(char* lid)
{
    open_status os;
    int index = open_device(lid, &os, "gyroscope");

    // 如果打开失败
    if (index == -1) return -1;

    // 如果已经打开，则直接返回之前的索引号index
    if(os == ALREADY_OPEN) return index;

    devp = get_open_device(index);
    if (has_operation_complemented(devp->private_data,
                                   GYROSCOPE_OPEN_INDEX))
    {
        gdop = devp->device_operation;
        gdop->general_gyroscope_open(devp->private_data, NULL);
    }

    return index;
}

int gyroscope_getx(int index, void* data)
{
    return gyroscope_get_helper(index, GYROSCOPE_GETX_INDEX, __func__, data);
}


int gyroscope_gety(int index, void* data)
{
    return gyroscope_get_helper(index, GYROSCOPE_GETY_INDEX, __func__, data);
}


int gyroscope_getz(int index, void* data)
{
    return gyroscope_get_helper(index, GYROSCOPE_GETZ_INDEX, __func__, data);
}


int gyroscope_getxyz(int index, void* data)
{
    return gyroscope_get_helper(index, GYROSCOPE_GETXYZ_INDEX, __func__, data);
}


static int gyroscope_get_helper
(
   int dev_open_idx, 
   int op_idx, 
   const char* func_name,
   void* data
)
{
    int result = -1;

    devp = get_open_device(dev_open_idx);
    assure_not_null(__FILE__, func_name, "devp", devp);
    
    // 检查设备的类型是否为gyroscope
    if (! check_device_type(devp, "gyroscope")) return -1;

    gdop = devp->device_operation;
    void* private_data = devp->private_data;
    if (has_operation_complemented(private_data, op_idx)){
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
        fprintf(stderr, "%s", msg);
    }

    return result;
}
