#include "device_open.h"
#include "magnetometer.h"
#include "magnetometer_match.h"
#include "error_report.h"
#include "device.h"
#include <stdio.h>
#include <string.h>

static struct device* devp;
static struct magnetometer_device_operation* mdop;

int magnetometer_open(char* lid)
{
    open_status os;
    int index = open_device(lid, &os, "magnetometer");
   
    // 如果打开失败
    if (index == -1) return -1;
    
    // 如果已经打开，则直接返回之前的索引号index
    if(os == ALREADY_OPEN) return index;
    
    devp = get_open_device(index);
    if (has_operation_complemented(devp->private_data, 
                                   MAGNETOMETER_OPEN_INDEX))
    {
       mdop = devp->device_operation;   
       mdop->general_magnetometer_open(devp->private_data, NULL);
    }

    return index;
}


int magnetometer_getx(int index, void* data)
{
    return magnetometer_get_helper(index, 
                                   MAGNETOMETER_GETX_INDEX,
                                   __func__, 
                                   data);
}


int magnetometer_gety(int index, void* data)
{
    return magnetometer_get_helper(index,
                                   MAGNETOMETER_GETY_INDEX,
                                   __func__, 
                                   data);
}


int magnetometer_getz(int index, void* data)
{
    return magnetometer_get_helper(index, 
                                   MAGNETOMETER_GETZ_INDEX, 
                                   __func__, 
                                   data);
}


int magnetometer_getxyz(int index, void* data)
{
    return magnetometer_get_helper(index,
                                   MAGNETOMETER_GETXYZ_INDEX,
                                   __func__,
                                   data);
}


static int magnetometer_get_helper
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
    
    // 检查设备的类型是否为magnetometer
    if (! check_device_type(devp, "magnetometer")) return -1;

    mdop = devp->device_operation;
    void* private_data = devp->private_data;
    if (has_operation_complemented(private_data, op_idx)){
         switch (op_idx){
               case MAGNETOMETER_GETX_INDEX: 
                    result =  mdop->general_magnetometer_getx(private_data,
                                                              data); 
                    break;
               case MAGNETOMETER_GETY_INDEX: 
                    result =  mdop->general_magnetometer_gety(private_data,
                                                              data); 
                    break;
               case MAGNETOMETER_GETZ_INDEX: 
                    result =  mdop->general_magnetometer_getz(private_data,
                                                              data); 
                    break;
               case MAGNETOMETER_GETXYZ_INDEX: 
                    result =  mdop->general_magnetometer_getxyz(private_data,
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

