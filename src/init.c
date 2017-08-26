#include "init.h"
#include "device.h"
#include "driver.h"
#include "dev_t.h"
#include "xml_operation.h"
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

#if DEBUG
    printf("\n---------------------------End init-------------------------\n");
#endif
}
