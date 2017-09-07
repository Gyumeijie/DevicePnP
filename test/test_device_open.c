#include "init.h"
#include "gyroscope.h"
#include "magnetometer.h"
#include "magnetorquer.h"
#include "load_xml.h"
#include "XmlParser.h"
#include <stdio.h>

int main()
{
   int fd1, fd2, fd3;
   unsigned int data;
   unsigned int data_arr[3] = {111, 222, 333};

   mxml_node_t* xml = get_xml_tree();
   parseXml(xml);
   printList();

   if(!init()) return 1;
   release_xml_tree();
  
   fd1 = gyroscope_open("gyroscope1");
   fd3 = magnetorquer_open("magnetorquer1");
   fd2 = gyroscope_open("gyroscope2");
   printf("gyroscope1 has fd: %d\n", fd1);
   printf("gyroscope2 has fd: %d\n", fd2);
   printf("magnetorquer1 has fd: %d\n", fd3);


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


   if (magnetorquer_setx(fd3, &data) != -1){
        printf("data read %d\n", data);
   }


   if (magnetorquer_setxyz(fd3, data_arr) != -1){
       int i;
       for (i=0; i<3; i++){
          printf("data write %d\n", data_arr[i]);
       }
   }

   return 0;
}
