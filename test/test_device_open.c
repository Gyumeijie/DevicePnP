#include "init.h"
#include "gyroscope.h"
#include "analogsunsensor.h"
#include <stdio.h>

int main()
{
   if(!init()) return 1;
  
   int fd1, fd2, fd3;

   unsigned int data;
   fd1 = gyroscope_open("gyroscope1");
   fd1 = gyroscope_open("gyroscope1");
   printf("gyroscope1 has fd: %d\n", fd1);

   fd2 = gyroscope_open("gyroscope2");
   printf("gyroscope2 has fd: %d\n", fd2);

   if (gyroscope_getx(fd1, &data) != -1){
     printf("data read %d\n", data);
   }
   
   if (gyroscope_getx(fd2, &data) != -1){
     printf("data read %d\n", data);
   }
  
   if(gyroscope_gety(fd1, &data) != -1){
      printf("data read %d\n", data);
   }
   
   if(gyroscope_getz(fd1, &data) != -1){
      printf("data read %d\n", data);
   }




   fd3 = analogsunsensor_open("analogsunsensor1");
   printf("analogsunsensor1 has fd: %d\n", fd3);
   analogsunsensor_read(fd3, &data);
   printf("data read %d\n", data);

   return 0;
}
