#include "init.h"
#include "gyroscope.h"
#include "analogsunsensor.h"
#include <stdio.h>

int main()
{
   if(!init()) return 1;
  
   int fd;

   unsigned int data;
   fd = gyroscope_open("gyroscope1");
   fd = gyroscope_open("gyroscope1");
   printf("gyroscope1 has fd: %d\n", fd);
   gyroscope_getx(fd, &data);
   printf("data read %d\n", data);
   gyroscope_gety(fd, &data);
   printf("data read %d\n", data);
   gyroscope_getz(fd, &data);
   printf("data read %d\n", data);

   fd = analogsunsensor_open("analogsunsensor1");
   printf("analogsunsensor1 has fd: %d\n", fd);
   analogsunsensor_read(fd, &data);
   printf("data read %d\n", data);

   return 0;
}
