#include "init.h"
#include "gyroscope.h"
#include "magnetometer.h"
#include "magnetorquer.h"
#include "flywheel.h"
#include "load_xml.h"
#include "XmlParser.h"
#include "parameter_package.h"
#include "command_sequence_fill.h"
#include "bytes_array_assembly.h"
#include <stdio.h>

int main()
{
   
   mxml_node_t* xml = get_xml_tree();
   parseXml(xml);

   if(!init()) return 1;
   release_xml_tree();

   int fd1 = flywheel_open("flywheel1");

   struct parameter_package* para_pkgp;

   int speed_code = 0x01020304;

   // TODO 当speed_code 下层应该能够捕获这个变化
   para_pkgp = init_parameter_package(2, 0);
   put_address(para_pkgp, &speed_code, "int");
   put_address(para_pkgp, &speed_code, "int");
   flywheel_set_speed(fd1, para_pkgp);
   destroy_parameter_package(para_pkgp);

   int left_xk, right_xk;
   float SunT;
   float BmqSW;
   //边界对齐问题 ch1和ch2将不会按照声明的顺序，而是会在调整到left_xk前面
   short int ch1, ch2;

   para_pkgp = init_parameter_package(6, 0); 
   //TODO 可以将其换成宏定义
   put_address(para_pkgp, &left_xk, "int");
   put_address(para_pkgp, &right_xk, "int");
   put_address(para_pkgp, &SunT, "float");
   put_address(para_pkgp, &BmqSW, "float");
   put_address(para_pkgp, &ch1, "int_l16");
   put_address(para_pkgp, &ch2, "int_l16");
   flywheel_receive(fd1, para_pkgp);
   destroy_parameter_package(para_pkgp);

   printf("left %08x\n", left_xk);
   printf("right %08x\n", right_xk); 
   printf("sunT %f\n", SunT);
   printf("BmqSW %f\n", BmqSW);
   printf("ch1 %08x\n", ch1);
   printf("ch2 %08x\n", ch2);

   return 0;
}
