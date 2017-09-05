#include "driver.h"
#include "dev_t.h"
#include "analogsunsensor_driver.h"
#include "analogsunsensor.h"
#include "adda_operation.h"
#include <stdio.h>

static int template_id;
static void* para_struct;

static void general_analogsunsensor_open(void* private_data){}

static int general_analogsunsensor_read(void* private_data, unsigned int* data)
{
    int result;

    fetch_data(private_data, ANALOGSUNSENSOR_READ_INDEX);
#if DEBUG
    printf("analogsunsensor_read is called with template_id: %d\n", template_id);
#endif
    switch (template_id){
        case 0 : result = analogsunsensor_read_template0(para_struct, data);
                 break;
        default: break;
    }

    return result;
}


static int analogsunsensor_read_template0(void* para_struct, unsigned int* data) 
{
    struct plain_array* open_template0 = para_struct;
    unsigned int len = open_template0->len;
    unsigned int* arr = open_template0->arr;

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


static struct analogsunsensor_device_operation ado = {
    general_analogsunsensor_open,
    general_analogsunsensor_read
};


static struct driver analogsunsensor_driver = {
    "ad",
     (void*)&ado,
     analogsunsensor_match
};


void analogsunsensor_driver_loader(void)
{
    int major = type2major("analogsunsensor");
    add_driver(major, &analogsunsensor_driver);
}
