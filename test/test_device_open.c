#include "device_register.h"
#include "driver_register.h"
#include "driver_bind.h"
#include "init.h"
#include "gyroscope.h"
#include "analogsunsensor.h"
#include <stdio.h>

int main()
{
   init();
   register_devices();
   register_drivers();
   bind_drivers();

   int fd;

   fd = gyroscope_open("gyroscope1");
   fd = gyroscope_open("gyroscope1");
   printf("gyroscope1 has fd: %d\n", fd);
   gyroscope_getx(fd);


   fd = analogsunsensor_open("analogsunsensor1");
   printf("analogsunsensor1 has fd: %d\n", fd);
   analogsunsensor_read(fd);
}
