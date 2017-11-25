#include "init.h"
#include "device.h"
#include "driver.h"
#include "device_register.h"
#include "driver_register.h"
#include "driver_bind.h"
#include "dev_t.h"
#include "config_info_collect.h"
#include "device_open.h"
#include "error_report.h"
#include "interpreter.h"
#include <stdio.h>

int init(void)
{
    device_init();
    devt_init();
    driver_init();
    interpreter_init(); 

    if(!config_info_collect_init()) return FAILURE; 
    device_open_init();

    if(!register_devices()) return FAILURE;
    register_drivers();
    if(!bind_drivers()) return FAILURE;
    return SUCCESS;
}
