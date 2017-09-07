#include "driver.h"
#include "dev_t.h"
#include "magnetorquer_driver.h"
#include "magnetorquer.h"
#include "adda_operation.h"
#include <stdio.h>

static int template_id;
static void* para_struct;

static void general_magnetorquer_open(void* private_data){}

static int general_magnetorquer_setx(void* private_data, unsigned int* data)
{
    int result;

    fetch_data(private_data, MAGNETORQUER_SETX_INDEX);
#if DEBUG
    printf("magnetorquer_setx is called with template_id: %d\n", template_id);
#endif
    switch (template_id){
        case 0 : result = magnetorquer_setx_template0(para_struct, data);
                 break;
        default: break;
    }

    return result;
}


static int general_magnetorquer_sety(void* private_data, unsigned int* data)
{
    int result;

    fetch_data(private_data, MAGNETORQUER_SETY_INDEX);
#if DEBUG
    printf("magnetorquer_sety is called with template_id: %d\n", template_id);
#endif
    switch (template_id){
        case 0 : result = magnetorquer_sety_template0(para_struct, data);
                 break;
        default: break;
    }

    return result;
}


static int general_magnetorquer_setz(void* private_data, unsigned int* data)
{
    int result;

    fetch_data(private_data, MAGNETORQUER_SETZ_INDEX);
#if DEBUG
    printf("magnetorquer_setz is called with template_id: %d\n", template_id);
#endif
    switch (template_id){
        case 0 : result = magnetorquer_setz_template0(para_struct, data);
                 break;
        default: break;
    }

    return result;
}

static int general_magnetorquer_setxyz(void* private_data, unsigned int* data)
{
    int result;

    fetch_data(private_data, MAGNETORQUER_SETXYZ_INDEX);
#if DEBUG
    printf("magnetorquer_setxyz is called with template_id: %d\n", template_id);
#endif
    switch (template_id){
        case 0 : result = magnetorquer_setxyz_template0(para_struct, data);
                 break;
        default: break;
    }

    return result;
}


static int magnetorquer_setx_template0(void* para_struct, unsigned int* data) 
{
    return set_pattern0(para_struct, data);
}


static int magnetorquer_sety_template0(void* para_struct, unsigned int* data) 
{
    return set_pattern0(para_struct, data);
}


static int magnetorquer_setz_template0(void* para_struct, unsigned int* data) 
{
    return set_pattern0(para_struct, data);
}


static int magnetorquer_setxyz_template0(void* para_struct, unsigned int* data) 
{
    return set_pattern0(para_struct, data);
}


static int set_pattern0(void* para_struct, unsigned int* data)
{
    struct plain_array* set_pat0p = para_struct;
    unsigned int len = set_pat0p->len;
    unsigned int* arr = set_pat0p->arr;

    return da_devices_write(data, len, arr);
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


static struct magnetorquer_device_operation mdo = {
    general_magnetorquer_open,
    general_magnetorquer_setx,
    general_magnetorquer_sety,
    general_magnetorquer_setz,
    general_magnetorquer_setxyz
};


static struct driver magnetorquer_driver = {
    "da",
     (void*)&mdo,
     magnetorquer_match
};


void magnetorquer_driver_loader(void)
{
    int major = type2major("magnetorquer");
    add_driver(major, &magnetorquer_driver);
}
