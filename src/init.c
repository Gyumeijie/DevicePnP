#include "init.h"
#include "device.h"
#include "driver.h"
#include "device_register.h"
#include "driver_register.h"
#include "driver_bind.h"
#include "dev_t.h"
#include "xml_operation.h"
#include "device_open.h"
#include <stdio.h>

void init(void)
{
#if DEBUG
    printf("\n-------------------------Begin init-----------------------\n\n");
#endif

    device_init();
    devt_init();
    driver_init();
    xml_operation_init();
    device_open_init();

    register_devices();
    register_drivers();
    bind_drivers();
#if DEBUG
    printf("\n---------------------------End init-------------------------\n");
#endif
}
