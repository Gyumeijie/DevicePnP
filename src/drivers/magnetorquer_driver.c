#include "driver.h"
#include "dev_t.h"
#include "magnetorquer_driver.h"
#include "magnetorquer.h"
#include "driver_supported_interface.h"

static int template_id;
static void* para_struct;

static int general_magnetorquer_open(void* private_data, void* data)
{
    fetch_data(private_data, MAGNETORQUER_OPEN_INDEX);
    return  magnetorquer_open_templates[template_id](para_struct, data);
}

static int general_magnetorquer_setx(void* private_data, void* data)
{

    fetch_data(private_data, MAGNETORQUER_SETX_INDEX);
    return  magnetorquer_setx_templates[template_id](para_struct, data);
}


static int general_magnetorquer_sety(void* private_data, void* data)
{
    fetch_data(private_data, MAGNETORQUER_SETY_INDEX);
    return  magnetorquer_sety_templates[template_id](para_struct, data);
}


static int general_magnetorquer_setz(void* private_data, void* data)
{
    fetch_data(private_data, MAGNETORQUER_SETZ_INDEX);
    return  magnetorquer_setz_templates[template_id](para_struct, data);
}

static int general_magnetorquer_setxyz(void* private_data, void* data)
{
    fetch_data(private_data, MAGNETORQUER_SETXYZ_INDEX);
    return  magnetorquer_setxyz_templates[template_id](para_struct, data);
}


static void fetch_data(void* private_data, int op_idx)
{
    template_id = ((struct template_data*)private_data)[op_idx].template_id;
    para_struct = ((struct template_data*)private_data)[op_idx].para_struct;
}


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
    add_driver(major, &magnetorquer_driver);
}
