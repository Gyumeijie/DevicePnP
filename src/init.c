#include "init.h"
#include "device.h"
#include "driver.h"
#include "device_register.h"
#include "driver_register.h"
#include "driver_bind.h"
#include "dev_t.h"
#include "xml_operation.h"
#include "device_open.h"
#include "error_report.h"
#include <stdio.h>

int init(void)
{
    device_init();
    devt_init();
    driver_init();
    if(!xml_operation_init()) return FAILURE; 
    device_open_init();

    if(!register_devices()) return FAILURE;
    register_drivers();
    if(!bind_drivers()) return FAILURE;

    return SUCCESS;
}
