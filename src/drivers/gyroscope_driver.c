#include "driver.h"
#include "dev_t.h"
#include "gyroscope_driver.h"
#include "gyroscope.h"
#include "template_data_fetch.h"
#include "driver_supported_interface.h"

static int template_id;
static void* para_struct;

static int general_gyroscope_open(void* private_data, void* data)
{ 
    fetch_data_template(private_data, 
                        GYROSCOPE_OPEN_INDEX,
                        &template_id, 
                        &para_struct);

    return  gyroscope_open_templates[template_id](para_struct, data);
}


static int general_gyroscope_getx(void* private_data, void* data)
{
    fetch_data_template(private_data, 
                        GYROSCOPE_GETX_INDEX,
                        &template_id, 
                        &para_struct);

    return gyroscope_getx_templates[template_id](para_struct, data);
}


static int general_gyroscope_gety(void* private_data, void* data)
{
    fetch_data_template(private_data,
                        GYROSCOPE_GETY_INDEX,
                        &template_id, 
                        &para_struct);

    return gyroscope_gety_templates[template_id](para_struct, data);
}


static int general_gyroscope_getz(void* private_data, void* data)
{
    fetch_data_template(private_data, 
                        GYROSCOPE_GETZ_INDEX,
                        &template_id, 
                        &para_struct);
    
    return gyroscope_getz_templates[template_id](para_struct, data);
}


static int general_gyroscope_getxyz(void* private_data, void* data)
{
    fetch_data_template(private_data, 
                        GYROSCOPE_GETXYZ_INDEX,
                        &template_id, 
                        &para_struct);

    return gyroscope_getxyz_templates[template_id](para_struct, data);
}


// Warning 添加新的操作函数的时候记得一定要同步gdo，不然会报错的
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
    // 如果添加了支持其它接口的gyroscope_driver，只需要在下面添加
    // add_supported_interface(&driver_supported_interfaces, new_interface);
    
    add_driver(major, &gyroscope_driver);
}
