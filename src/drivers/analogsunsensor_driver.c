#include "driver.h"
#include "dev_t.h"
#include "analogsunsensor_driver.h"
#include "analogsunsensor_common.h"
#include "adda_operation.h"
#include <stdio.h>


static int template_id;
static void* para_struct;

#if 0
static int analogsunsensor_match(void)
{
    return do_match(init_template_data_table, 
                    find_and_exec_match_func, undo_match);
}
#endif

static void analogsunsensor_open(void* private_data)
{
#if DEBUG
    printf("analogsunsensor_open is called\n");
#endif 
}

static void analogsunsensor_open_template0(void* para_struct)
{


}

static void analogsunsensor_read(void* private_data)
{
    template_id = ((struct template_data*)private_data)[ANALOGSUNSENSOR_READ_INDEX].template_id;
    para_struct = ((struct template_data*)private_data)[ANALOGSUNSENSOR_READ_INDEX].para_struct;

    switch (template_id){
        case 0 : analogsunsensor_read_template0(para_struct);
                 break;
        default: break;
    }
}


static void analogsunsensor_read_template0(void* para_struct) 
{
    struct plain_array* open_template0 = para_struct;
    unsigned int len = open_template0->len;
    unsigned int* arr = open_template0->arr;

#if DEBUG
    int i;
    for (i=0; i<len; i++){
       printf("channel: %d\n", arr[i]);
    }
#endif 
    static unsigned int data[10];
    //fill plain array
    ad_devices_read(data, len, arr);

#if DEBUG
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
#if DEBUG
    printf("analogsunsensor driver loader is being called\n");
#endif 
    add_driver(major, &analogsunsensor_driver);
}
