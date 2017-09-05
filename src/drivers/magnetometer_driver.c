#include "driver.h"
#include "dev_t.h"
#include "magnetometer_driver.h"
#include "magnetometer.h"
#include "adda_operation.h"
#include <stdio.h>

static int template_id;
static void* para_struct;

static void general_magnetometer_open(void* private_data){}

static int general_magnetometer_getx(void* private_data, unsigned int* data)
{
    int result;

    fetch_data(private_data, MAGNETOMETER_GETX_INDEX);
#if DEBUG
    printf("magnetometer_getx is called with template_id: %d\n", template_id);
#endif
    switch (template_id){
        case 0 : result = magnetometer_getx_template0(para_struct, data);
                 break;
        default: break;
    }

    return result;
}


static int general_magnetometer_gety(void* private_data, unsigned int* data)
{
    int result;

    fetch_data(private_data, MAGNETOMETER_GETY_INDEX);
#if DEBUG
    printf("magnetometer_gety is called with template_id: %d\n", template_id);
#endif
    switch (template_id){
        case 0 : result = magnetometer_gety_template0(para_struct, data);
                 break;
        default: break;
    }

    return result;
}


static int general_magnetometer_getz(void* private_data, unsigned int* data)
{
    int result;

    fetch_data(private_data, MAGNETOMETER_GETZ_INDEX);
#if DEBUG
    printf("magnetometer_getz is called with template_id: %d\n", template_id);
#endif
    switch (template_id){
        case 0 : result = magnetometer_getz_template0(para_struct, data);
                 break;
        default: break;
    }

    return result;
}

static int general_magnetometer_getxyz(void* private_data, unsigned int* data)
{
    int result;

    fetch_data(private_data, MAGNETOMETER_GETXYZ_INDEX);
#if DEBUG
    printf("magnetometer_getxyz is called with template_id: %d\n", template_id);
#endif
    switch (template_id){
        case 0 : result = magnetometer_getxyz_template0(para_struct, data);
                 break;
        default: break;
    }

    return result;
}


static int magnetometer_getx_template0(void* para_struct, unsigned int* data) 
{
    return get_pattern0(para_struct, data);
}


static int magnetometer_gety_template0(void* para_struct, unsigned int* data) 
{
    return get_pattern0(para_struct, data);
}


static int magnetometer_getz_template0(void* para_struct, unsigned int* data) 
{
    return get_pattern0(para_struct, data);
}


static int magnetometer_getxyz_template0(void* para_struct, unsigned int* data) 
{
    return get_pattern0(para_struct, data);
}


static int get_pattern0(void* para_struct, unsigned int* data)
{
    struct plain_array* get_pat0p = para_struct;
    unsigned int len = get_pat0p->len;
    unsigned int* arr = get_pat0p->arr;

    return ad_devices_read(data, len, arr);
}


/**
 *　输入：配置信息结构体指针private以及设备操作的索引号op_idx
 *　输出：无
 *　功能：根据设备操作的索引号将设备操作的配置信息取出来
 */
static void fetch_data(void* private_data, int op_idx)
{
    template_id = ((struct template_data*)private_data)[op_idx].template_id;
    para_struct = ((struct template_data*)private_data)[op_idx].para_struct;
}


static struct magnetometer_device_operation mdo = {
    general_magnetometer_open,
    general_magnetometer_getx,
    general_magnetometer_gety,
    general_magnetometer_getz,
    general_magnetometer_getxyz
};


static struct driver magnetometer_driver = {
    "ad",
     (void*)&mdo,
     magnetometer_match
};


void magnetometer_driver_loader(void)
{
    int major = type2major("magnetometer");
    add_driver(major, &magnetometer_driver);
}
