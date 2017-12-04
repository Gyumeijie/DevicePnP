#include "driver.h"
#include "dev_t.h"
#include "parameter_package.h"
#include "flywheel_driver.h"
#include "flywheel.h"
#include "data_template_fetch.h"
#include "driver_supported_interface.h"
#include <stdio.h>

static int template_id;
static void* para_struct;

static int general_flywheel_open(void* private_data, void* para)
{ 
    fetch_data_template(private_data,
                        FLYWHEEL_OPEN_INDEX,
                        &template_id, 
                        &para_struct);

    return flywheel_open_templates[template_id](para_struct, para);
}


static int general_flywheel_set_speed(void* private_data, void* para)
{
    fetch_data_template(private_data,
                        FLYWHEEL_SET_SPEED_INDEX,
                        &template_id, 
                        &para_struct);

    return flywheel_set_speed_templates[template_id](para_struct, para); 
}


static int general_flywheel_receive(void* private_data, void* para)
{
    fetch_data_template(private_data, 
                        FLYWHEEL_RECEIVE_INDEX,
                        &template_id, 
                        &para_struct);

    return flywheel_receive_templates[template_id](para_struct, para); 
}


// Warning 添加新的操作函数的时候记得一定要同步fdo，不然会报错的
static struct flywheel_device_operation fdo = {
    general_flywheel_open,
    general_flywheel_set_speed,
    general_flywheel_receive
};


static interface_t driver_supported_interfaces;
static struct driver flywheel_driver = {
    &driver_supported_interfaces,
    (void*)&fdo,
    flywheel_match
};


void flywheel_driver_loader(void)
{
    int major = type2major("flywheel");
    
    add_supported_interface(&driver_supported_interfaces, "i2c");
    add_supported_interface(&driver_supported_interfaces, "rs422");
    // 如果添加了支持其它接口的flywheel_driver，只需要在下面添加
    // add_supported_interface(&driver_supported_interfaces, new_interface);

    add_driver(major, &flywheel_driver);
}
