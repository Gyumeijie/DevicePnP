#include "driver.h"
#include "dev_t.h"
#include "gyroscope_driver.h"
#include "gyroscope_common.h"
#include <stdio.h>

static int template_id;
static void* para_struct;

static void gyroscope_open(void* private_data)
{ 
    fetch_data(private_data, GYROSCOPE_OPEN_INDEX);
#if DEBUG
    printf("gyroscope_open is called with template_id: %d\n", template_id);
#endif
   switch(template_id){
       case 0 : gyroscope_open_template0(para_struct);
                break;
       default: break;
   }
}


static void gyroscope_open_template0(void* para_struct)
{ 
    struct reg_array* open_template0 = para_struct;
    int len = open_template0->len;
    struct reg* regp = open_template0->regp;

    int i;
    for (i=0; i<len; i++){
       char reg_address = regp[i].addr;
       char data = regp[i].val;
#if DEBUG
       printf("address: 0x%02x data:0x%02x\n", reg_address, data);
#endif
       //i2c写寄存器函数
    }
}


static int gyroscope_getx(void* private_data, unsigned int* data)
{
    int result;

    fetch_data(private_data, GYROSCOPE_GETX_INDEX);
#if DEBUG
    printf("gyroscope_getx is called with template_id: %d\n", template_id);
#endif
    switch(template_id){
        case 0: result = gyroscope_getx_template0(para_struct, data);
                break;
        default:break;
    }
  
   return result;
}


static int gyroscope_getx_template0(void* para_struct, unsigned int* data)
{
    return get_pattern0(para_struct, data);
}


static int gyroscope_gety(void* private_data, unsigned int* data)
{
    int result;

    fetch_data(private_data, GYROSCOPE_GETY_INDEX);
#if DEBUG
    printf("gyroscope_gety is called with template_id: %d\n", template_id);
#endif
    switch(template_id){
        case 0: result = gyroscope_gety_template0(para_struct, data);
                break;
        default:break;
    }
    
   return result;
}


static int gyroscope_gety_template0(void* para_struct, unsigned int* data)
{
    return get_pattern0(para_struct, data);
}


static int gyroscope_getz(void* private_data, unsigned int* data)
{
    int result;

    fetch_data(private_data, GYROSCOPE_GETZ_INDEX);
#if DEBUG
    printf("gyroscope_getz is called with template_id: %d\n", template_id);
#endif
    switch(template_id){
        case 0: result = gyroscope_getz_template0(para_struct, data);
                break;
        default:break;
    }
    
   return result;
}


static int gyroscope_getz_template0(void* para_struct, unsigned int* data)
{
    return get_pattern0(para_struct, data);
}


static int gyroscope_getxyz(void* private_data, unsigned int* data)
{
    int result;

    fetch_data(private_data, GYROSCOPE_GETXYZ_INDEX);
#if DEBUG
    printf("gyroscope_getxyz is called with template_id: %d\n", template_id);
#endif
    switch(template_id){
        case 0: result = gyroscope_getxyz_template0(para_struct, data);
                break;
        default:break;
    }

   return result;
}


static int gyroscope_getxyz_template0(void* para_struct, unsigned int* data)
{
    return get_pattern0(para_struct, data);
}


static int get_pattern0(void* para_struct, unsigned int* data)
{
    struct get_reg_pattern0* getreg_pat0p = para_struct;
#if DEBUG
    char reg_address = getreg_pat0p->reg_address;
    int size = getreg_pat0p->size;
    printf("address: 0x%02x size:%d\n", reg_address, size);
    //模拟i2c读寄存器函数
    *data = reg_address;
    return size;
#endif
}


static void fetch_data(void* private_data, int index)
{
    template_id = ((struct template_data*)private_data)[index].template_id;
    para_struct = ((struct template_data*)private_data)[index].para_struct;
}


static struct gyroscope_device_operation gdo = {
    gyroscope_open,
    gyroscope_getx,
    gyroscope_gety,
    gyroscope_getz,
    gyroscope_getxyz
};

static struct driver gyroscope_driver = {
    "i2c",
     (void*)&gdo,
     gyroscope_match
};

void gyroscope_driver_loader(void)
{
    int major = type2major("gyroscope");
    add_driver(major, &gyroscope_driver);
}
