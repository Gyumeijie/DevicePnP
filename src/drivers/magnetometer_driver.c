#include "driver.h"
#include "dev_t.h"
#include "magnetometer_driver.h"
#include "magnetometer.h"
#include "data_template_fetch.h"
#include "driver_supported_interface.h"

static int template_id;
static void* para_struct;

static int general_magnetometer_open(void* private_data, void* data)
{
    fetch_data_template(private_data, 
                        MAGNETOMETER_OPEN_INDEX,
                        &template_id, 
                        &para_struct);

    return  magnetometer_open_templates[template_id](para_struct, data);
}

static int general_magnetometer_getx(void* private_data, void* data)
{
    fetch_data_template(private_data, 
                        MAGNETOMETER_GETX_INDEX,
                        &template_id, 
                        &para_struct);

    return  magnetometer_getx_templates[template_id](para_struct, data);
}


static int general_magnetometer_gety(void* private_data, void* data)
{
    fetch_data_template(private_data, 
                        MAGNETOMETER_GETY_INDEX,
                        &template_id, 
                        &para_struct);

    return  magnetometer_gety_templates[template_id](para_struct, data);
}


static int general_magnetometer_getz(void* private_data, void* data)
{
    fetch_data_template(private_data,
                        MAGNETOMETER_GETZ_INDEX,
                        &template_id, 
                        &para_struct);
                        
    return  magnetometer_gety_templates[template_id](para_struct, data);
}


static int general_magnetometer_getxyz(void* private_data, void* data)
{
    fetch_data_template(private_data, 
                        MAGNETOMETER_GETXYZ_INDEX,
                        &template_id, 
                        &para_struct);

    return  magnetometer_gety_templates[template_id](para_struct, data);
}


// Warning 添加新的操作函数的时候记得一定要同步mdo，不然会报错的
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
    // 如果添加了支持其它接口的magnetometer_driver，只需要在下面添加
    // add_supported_interface(&driver_supported_interfaces, new_interface);
    
    add_driver(major, &magnetometer_driver);
}
