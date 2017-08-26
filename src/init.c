#include "init.h"
#include "device.h"
#include "driver.h"
#include "dev_t.h"

void init(void)
{
    device_init();
    devt_init();
    driver_init();
}
