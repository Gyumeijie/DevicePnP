#include "driver.h"
#include "dev_t.h"
#include "magnetorquer_driver.h"
#include "magnetorquer.h"
#include "template_data_fetch.h"
#include "driver_supported_interface.h"

static int template_id;
static void* para_struct;


static int general_magnetorquer_open(void* private_data, void* data)
{
    fetch_data_template(private_data, 
                        MAGNETORQUER_OPEN_INDEX,
                        &template_id, 
                        &para_struct);

    return  magnetorquer_open_templates[template_id](para_struct, data);
}


static int general_magnetorquer_setx(void* private_data, void* data)
{

    fetch_data_template(private_data, 
                        MAGNETORQUER_SETX_INDEX,
                        &template_id, 
                        &para_struct);

    return  magnetorquer_setx_templates[template_id](para_struct, data);
}


static int general_magnetorquer_sety(void* private_data, void* data)
{
    fetch_data_template(private_data, 
                        MAGNETORQUER_SETY_INDEX,
                        &template_id, 
                        &para_struct);

    return  magnetorquer_sety_templates[template_id](para_struct, data);
}


static int general_magnetorquer_setz(void* private_data, void* data)
{
    fetch_data_template(private_data, 
                        MAGNETORQUER_SETZ_INDEX,
                        &template_id, 
                        &para_struct);

    return  magnetorquer_setz_templates[template_id](para_struct, data);
}


static int general_magnetorquer_setxyz(void* private_data, void* data)
{
    fetch_data_template(private_data, 
                        MAGNETORQUER_SETXYZ_INDEX,
                        &template_id, 
                        &para_struct);
    
    return  magnetorquer_setxyz_templates[template_id](para_struct, data);
}


// Warning 添加新的操作函数的时候记得一定要同步mdo，不然会报错的
static struct magnetorquer_device_operation mdo = {
    general_magnetorquer_open,
    general_magnetorquer_setx,
    general_magnetorquer_sety,
    general_magnetorquer_setz,
    general_magnetorquer_setxyz
};


static interface_t driver_supported_interfaces;
static struct driver magnetorquer_driver = {
     &driver_supported_interfaces,
     (void*)&mdo,
     magnetorquer_match
};


void magnetorquer_driver_loader(void)
{
    int major = type2major("magnetorquer");

    add_supported_interface(&driver_supported_interfaces, "da"); 
    // 如果添加了支持其它接口的magnetorquer_driver，只需要在下面添加
    // add_supported_interface(&driver_supported_interfaces, new_interface);
    
    add_driver(major, &magnetorquer_driver);
}
