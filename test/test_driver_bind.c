#include "device_register.h"
#include "driver_register.h"
#include "driver_bind.h"
#include <stdio.h>

int main()
{

   init();
   
   register_devices();
   register_drivers();
   bind_drivers();   
}
