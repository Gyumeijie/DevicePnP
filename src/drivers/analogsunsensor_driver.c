#include "driver.h"
#include "dev_t.h"
#include "analogsunsensor_driver.h"
#include "analogsunsensor.h"
#include "driver_supported_interface.h"

static int template_id;
static void* para_struct;

static int general_analogsunsensor_open(void* private_data, void* data)
{
    //没有实际的初始化工作
    fetch_data(private_data, ANALOGSUNSENSOR_OPEN_INDEX);
    return  analogsunsensor_open_templates[template_id](para_struct, data);
}


static int general_analogsunsensor_read(void* private_data, void* data)
{
    fetch_data(private_data, ANALOGSUNSENSOR_READ_INDEX);
    return  analogsunsensor_open_templates[template_id](para_struct, data);
}


static void fetch_data(void* private_data, int op_idx)
{
    template_id = ((struct template_data*)private_data)[op_idx].template_id;
    para_struct = ((struct template_data*)private_data)[op_idx].para_struct;
}


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
    add_driver(major, &analogsunsensor_driver);
}
