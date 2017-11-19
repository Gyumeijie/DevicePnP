#include "driver.h"
#include "dev_t.h"
#include "magnetometer_driver.h"
#include "magnetometer.h"
#include "driver_supported_interface.h"

static int template_id;
static void* para_struct;

static int general_magnetometer_open(void* private_data, void* data)
{
   //没有实际的初始化工作
    fetch_data(private_data, MAGNETOMETER_OPEN_INDEX);
    return  magnetometer_open_templates[template_id](para_struct, data);
}

static int general_magnetometer_getx(void* private_data, void* data)
{
    fetch_data(private_data, MAGNETOMETER_GETX_INDEX);
    return  magnetometer_getx_templates[template_id](para_struct, data);
}


static int general_magnetometer_gety(void* private_data, void* data)
{
    fetch_data(private_data, MAGNETOMETER_GETY_INDEX);
    return  magnetometer_gety_templates[template_id](para_struct, data);
}


static int general_magnetometer_getz(void* private_data, void* data)
{
    fetch_data(private_data, MAGNETOMETER_GETZ_INDEX);
    return  magnetometer_gety_templates[template_id](para_struct, data);
}


static int general_magnetometer_getxyz(void* private_data, void* data)
{
    fetch_data(private_data, MAGNETOMETER_GETXYZ_INDEX);
    return  magnetometer_gety_templates[template_id](para_struct, data);
}


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


static interface_t driver_supported_interfaces;
static struct driver magnetometer_driver = {
     &driver_supported_interfaces,
     (void*)&mdo,
     magnetometer_match
};


void magnetometer_driver_loader(void)
{
    int major = type2major("magnetometer");

    add_supported_interface(&driver_supported_interfaces, "ad"); 
    add_driver(major, &magnetometer_driver);
}
