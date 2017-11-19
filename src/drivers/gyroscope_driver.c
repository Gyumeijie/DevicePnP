#include "driver.h"
#include "dev_t.h"
#include "gyroscope_driver.h"
#include "gyroscope.h"
#include "driver_supported_interface.h"

static int template_id;
static void* para_struct;

static int general_gyroscope_open(void* private_data, void* data)
{ 
    //会执行相关的寄存器初始化工作
    fetch_data(private_data, GYROSCOPE_OPEN_INDEX);
    return  gyroscope_open_templates[template_id](para_struct, data);
}


static int general_gyroscope_getx(void* private_data, void* data)
{
    fetch_data(private_data, GYROSCOPE_GETX_INDEX);
    return gyroscope_getx_templates[template_id](para_struct, data);
}


static int general_gyroscope_gety(void* private_data, void* data)
{
    fetch_data(private_data, GYROSCOPE_GETY_INDEX);
    return gyroscope_gety_templates[template_id](para_struct, data);
}



static int general_gyroscope_getz(void* private_data, void* data)
{
    fetch_data(private_data, GYROSCOPE_GETZ_INDEX);
    return gyroscope_getz_templates[template_id](para_struct, data);
}


static int general_gyroscope_getxyz(void* private_data, void* data)
{
    fetch_data(private_data, GYROSCOPE_GETXYZ_INDEX);
    return gyroscope_getxyz_templates[template_id](para_struct, data);
}


static void fetch_data(void* private_data, int index)
{
    template_id = ((struct template_data*)private_data)[index].template_id;
    para_struct = ((struct template_data*)private_data)[index].para_struct;
}


static struct gyroscope_device_operation gdo = {
    general_gyroscope_open,
    general_gyroscope_getx,
    general_gyroscope_gety,
    general_gyroscope_getz,
    general_gyroscope_getxyz
};


static interface_t driver_supported_interfaces;
static struct driver gyroscope_driver = {
     &driver_supported_interfaces,
     (void*)&gdo,
     gyroscope_match
};


void gyroscope_driver_loader(void)
{
    int major = type2major("gyroscope");

    add_supported_interface(&driver_supported_interfaces, "i2c"); 
    add_driver(major, &gyroscope_driver);
}
