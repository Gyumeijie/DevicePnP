#include "driver_register.h"
#include "dev_t.h"
#include "init.h"
#include <stdio.h>

int main()
{
    init();
    register_drivers();
}
