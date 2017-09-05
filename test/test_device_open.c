#include "init.h"
#include "gyroscope.h"
#include "analogsunsensor.h"
#include "XmlParser.h"
#include <stdio.h>

int main()
{
   int fd1, fd2, fd3;
   unsigned int data;

   FILE* fp=fopen("device.xml","r");
   mxml_node_t* xml=mxmlLoadFile(NULL,fp,MXML_NO_CALLBACK);
   parseXml(xml);
   printList();
   fclose(fp);

   if(!init()) return 1;
  
   fd1 = gyroscope_open("gyroscope1");
   fd3 = analogsunsensor_open("analogsunsensor1");
   fd2 = gyroscope_open("gyroscope2");
   printf("gyroscope1 has fd: %d\n", fd1);
   printf("gyroscope2 has fd: %d\n", fd2);
   printf("analogsunsensor1 has fd: %d\n", fd3);


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

   if (analogsunsensor_read(fd3, &data) != -1){
     printf("data read %d\n", data);
   }

   return 0;
}
