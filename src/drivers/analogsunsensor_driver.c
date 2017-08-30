#include "driver.h"
#include "dev_t.h"
#include "analogsunsensor_driver.h"
#include "analogsunsensor_common.h"
#include "adda_operation.h"
#include <stdio.h>


static int template_id;
static void* para_struct;

static void analogsunsensor_open(void* private_data){}


static void analogsunsensor_read(void* private_data, unsigned int* data)
{
    template_id = ((struct template_data*)private_data)[ANALOGSUNSENSOR_READ_INDEX].template_id;
    para_struct = ((struct template_data*)private_data)[ANALOGSUNSENSOR_READ_INDEX].para_struct;

    switch (template_id){
        case 0 : analogsunsensor_read_template0(para_struct, data);
                 break;
        default: break;
    }
}


static void analogsunsensor_read_template0(void* para_struct, unsigned int* data) 
{
    struct plain_array* open_template0 = para_struct;
    unsigned int len = open_template0->len;
    unsigned int* arr = open_template0->arr;

    ad_devices_read(data, len, arr);
#if DEBUG
    int i;
    for (i=0; i<len; i++){
       printf("channel: %d  data: %d\n", arr[i], data[i]);
    }
#endif 
}

static struct analogsunsensor_device_operation ado = {
    analogsunsensor_open,
    analogsunsensor_read
};


static struct driver analogsunsensor_driver = {
    "ad",
     (void*)&ado,
     analogsunsensor_match
};


extern void analogsunsensor_driver_loader(void)
{
    int major = type2major("analogsunsensor");
    add_driver(major, &analogsunsensor_driver);
}
