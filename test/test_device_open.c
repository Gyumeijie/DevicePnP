#include "init.h"
#include "gyroscope.h"
#include "magnetometer.h"
#include "load_xml.h"
#include "XmlParser.h"
#include <stdio.h>

int main()
{
   int fd1, fd2, fd3;
   unsigned int data;
   unsigned int data_arr[3];

   mxml_node_t* xml = get_xml_tree();
   parseXml(xml);
   printList();

   if(!init()) return 1;
   release_xml_tree();
  
   fd1 = gyroscope_open("gyroscope1");
   fd3 = magnetometer_open("magnetometer1");
   fd2 = gyroscope_open("gyroscope2");
   printf("gyroscope1 has fd: %d\n", fd1);
   printf("gyroscope2 has fd: %d\n", fd2);
   printf("magnetometer1 has fd: %d\n", fd3);


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


   if (magnetometer_getxyz(fd3, data_arr) != -1){
       int i;
       for (i=0; i<3; i++){
          printf("data read %d\n", data_arr[i]);
       }
   }

   return 0;
}
