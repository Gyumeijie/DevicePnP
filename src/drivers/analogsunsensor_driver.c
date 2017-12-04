#include "driver.h"
#include "dev_t.h"
#include "analogsunsensor_driver.h"
#include "analogsunsensor.h"
#include "data_template_fetch.h"
#include "driver_supported_interface.h"

static int template_id;
static void* para_struct;

static int general_analogsunsensor_open(void* private_data, void* data)
{
    fetch_data_template(private_data,
                        ANALOGSUNSENSOR_OPEN_INDEX,
                        &template_id, 
                        &para_struct);

    return  analogsunsensor_open_templates[template_id](para_struct, data);
}


static int general_analogsunsensor_read(void* private_data, void* data)
{
    fetch_data_template(private_data, 
                        ANALOGSUNSENSOR_READ_INDEX,
                        &template_id, 
                        &para_struct);

    return  analogsunsensor_open_templates[template_id](para_struct, data);
}


// Warning 添加新的操作函数的时候记得一定要同步ado，不然会报错的
static struct analogsunsensor_device_operation ado = {
    general_analogsunsensor_open,
    general_analogsunsensor_read
};


static interface_t driver_supported_interfaces;
static struct driver analogsunsensor_driver = {
     &driver_supported_interfaces,
     (void*)&ado,
     analogsunsensor_match
};


void analogsunsensor_driver_loader(void)
{
    int major = type2major("analogsunsensor");
    
    add_supported_interface(&driver_supported_interfaces, "ad"); 
    // 如果添加了支持其它接口的analogsunsensor_driver，只需要在下面添加
    // add_supported_interface(&driver_supported_interfaces, new_interface);
    
    add_driver(major, &analogsunsensor_driver);
}
