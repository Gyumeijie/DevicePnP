#include "init.h"
#include "gyroscope.h"
#include "magnetometer.h"
#include "magnetorquer.h"
#include "flywheel.h"
#include "load_xml.h"
#include "XmlParser.h"
#include "parameter_package.h"
#include "command_sequence_generate.h"
#include "bytes_array_assembly.h"
#include <stdio.h>

/* helper functions */
void delay(int d)  
{
    for (int i =0; i<d; i++)
      for(int j=0; j<10000*10000; j++);
}

int main()
{
   
   mxml_node_t* xml = get_xml_tree();
   parseXml(xml);

   if(!init()) return 1;
   release_xml_tree();

   int fd = magnetorquer_open("magnetorquer1");
   unsigned int data= 0x3fff;
   unsigned int data1= 0x3000;
   while (1) {
     magnetorquer_setx(fd, &data);
     delay(1);
     magnetorquer_setx(fd, &data1);
     delay(1);
   }

   
   return 0;
}
