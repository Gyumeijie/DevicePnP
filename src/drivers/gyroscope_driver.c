#include "driver.h"
#include "dev_t.h"
#include "gyroscope_driver.h"
#include "gyroscope_common.h"
#include <stdio.h>

static int template_id;
static void* para_struct;

#if 0
//根据lid唯一标识的的设备配置信息去匹配
static int gyroscope_match(void)
{  
    return  do_match(init_template_data_table,
                     find_and_exec_match_func, undo_match);
}
#endif

/**
 *　输入：　
 *　输出：
 *　功能：
 */
static void gyroscope_open(void* private_data)
{ 
    template_id = ((struct template_data*)private_data)[GYROSCOPE_OPEN_INDEX].template_id;
    para_struct = ((struct template_data*)private_data)[GYROSCOPE_OPEN_INDEX].para_struct;
#if DEBUG
    printf("gyroscope_open is called\n");
    printf("template_id: %d\n", template_id);
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


/**
 *　输入：　
 *　输出：
 *　功能：
 */
static void gyroscope_getx(void* private_data, unsigned int* data)
{
    template_id = ((struct template_data*)private_data)[GYROSCOPE_GETX_INDEX].template_id;
    para_struct = ((struct template_data*)private_data)[GYROSCOPE_GETX_INDEX].para_struct;
#if DEBUG
    printf("gyroscope_getx is called\n");
    printf("template_id: %d\n", template_id);
#endif
    switch(template_id){
        case 0: gyroscope_getx_template0(para_struct, data);
                break;
        default:break;
    }
}


static void gyroscope_getx_template0(void* para_struct, unsigned int* data)
{
    struct getx_template0* getx_tpl0p = para_struct;
#if DEBUG
    char reg_address = getx_tpl0p->reg_address;
    int size = getx_tpl0p->size;
    printf("address: 0x%02x size:%d\n", reg_address, size);
    *data = 1;
#endif
    //i2c读寄存器函数
}


static struct gyroscope_device_operation gdo = {
    gyroscope_open,
    gyroscope_getx
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
