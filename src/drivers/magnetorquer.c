#include "device_open.h"
#include "magnetorquer.h"
#include "magnetorquer_match.h"
#include "error_report.h"
#include <stdio.h>
#include <string.h>

static struct device_open* devop;
static struct magnetorquer_device_operation* mdop;

int magnetorquer_open(char* lid)
{
    open_status os;
    int index = open_device(lid, &os, "magnetorquer");
   
    // 如果打开失败
    if (index == -1) return -1;
    
    // 如果已经打开，则直接返回之前的索引号index
    if(os == ALREADY_OPEN) return index;
    
    devop = get_device_open_struct(index);
    if (has_operation_complemented(devop->private_data, 
                                   MAGNETORQUER_OPEN_INDEX))
    {
       mdop = devop->device_operation;   
       mdop->general_magnetorquer_open(devop->private_data, NULL);
    }

    return index;
}


int magnetorquer_setx(int index, void* data)
{
    return magnetorquer_set_helper(index, 
                                   MAGNETORQUER_SETX_INDEX,
                                   __func__,
                                   data);
}


int magnetorquer_sety(int index, void* data)
{
    return magnetorquer_set_helper(index,
                                   MAGNETORQUER_SETY_INDEX,
                                   __func__, 
                                   data);
}


int magnetorquer_setz(int index, void* data)
{
    return magnetorquer_set_helper(index,
                                   MAGNETORQUER_SETZ_INDEX, 
                                   __func__, 
                                   data);
}


int magnetorquer_setxyz(int index, void* data)
{
    return magnetorquer_set_helper(index,
                                   MAGNETORQUER_SETXYZ_INDEX,
                                   __func__, 
                                   data);
}


static int magnetorquer_set_helper
(
    int dev_open_idx, 
    int op_idx, 
    const char* func_name,
    void* data
)
{
    int result = -1;

    devop = get_device_open_struct(dev_open_idx); 
    if (! check_null(__FILE__, __func__, "devop", devop)){
       printf("Detail: can't find device open struct with index %d\n",
                                                                 dev_open_idx);
       return -1;
    }
    
    // 检查设备的类型是否为magnetorquer
    if (! check_device_type(devop, "magnetorquer")) return -1;

    mdop = devop->device_operation;
    void* private_data = devop->private_data;
    if (has_operation_complemented(private_data, op_idx)){
         switch (op_idx){
               case MAGNETORQUER_SETX_INDEX: 
                    result =  mdop->general_magnetorquer_setx(private_data,
                                                              data); 
                    break;
               case MAGNETORQUER_SETY_INDEX: 
                    result =  mdop->general_magnetorquer_sety(private_data,
                                                              data); 
                    break;
               case MAGNETORQUER_SETZ_INDEX: 
                    result =  mdop->general_magnetorquer_setz(private_data,
                                                              data); 
                    break;
               case MAGNETORQUER_SETXYZ_INDEX: 
                    result =  mdop->general_magnetorquer_setxyz(private_data,
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
