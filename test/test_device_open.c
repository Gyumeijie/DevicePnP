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

void user_defined_compute_func(char* bytes_value, int size, void* para);
void post_proc
(
   const char* start_addr,
   int num_byte, 
   int asm_val,
   void* var_addr
 );

Boolean pretest(const char* bytes_arr, int arr_len);

int main()
{
   

   mxml_node_t* xml = get_xml_tree();
   parseXml(xml);

   if(!init()) return 1;
   release_xml_tree();
  


   int fd1 = flywheel_open("flywheel1");
   register_compute_func(3, user_defined_compute_func);
   inspect_compute_funcs_bitmap(4);

   struct parameter_package* para_pkgp;
   int speed_code = 0x00010203;

   para_pkgp = init_parameter_package(2, 0);
   put_value(para_pkgp, &speed_code, "int");
   put_value(para_pkgp, &speed_code, "int");
   flywheel_set_speed(fd1, para_pkgp);
   destroy_parameter_package(para_pkgp);


   int left_xk, right_xk;
   float SunT;
   float BmqSW;
   //边界对齐问题 ch1和ch2将不会按照声明的顺序，而是会在调整到left_xk前面
   short int ch1, ch2;
   int paras_pos[2] = {2, 3};
   register_post_processing_func_for_paras("flywheel1", 3, post_proc,
                                            paras_pos, 2);
   //TODO 将幻数3换成相应的宏
   register_precondition_function("flywheel1",/*表示函数flywheel_receive*/ 3,
                                  pretest);

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

   // static char bytesdata[16] = {
   //     0x00, 0x01, 0x02, 0x03, 0x00, 0x14, 0x00, 0x00,
   //     0x00, 0x28, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
   // };

   printf("%08x\n", left_xk);
   printf("%08x\n", right_xk); 
   printf("%f\n", SunT);
   printf("%f\n", BmqSW);
   printf("%08x\n", ch1);
   printf("%08x\n", ch2);

   return 0;
}

//TODO 考虑一下用户自己定义的函数的组织方法包括建议的文件名
//以及函数名的命名格式
void user_defined_compute_func(char* bytes_value, int size, void* para)
{
    //与具体应用相关的参数处理过程
    static int temp;
    temp = *(int*)para;
    temp = temp * 2 +  1; 

    //作为默认会调用的
    use_compute_func(0, bytes_value, size, &temp);
}


void post_proc
(
   const char* start_addr, 
   int num_byte, 
   int asm_val, 
   void* var_addr
)
{
    //区分变量 常量 以及 运算符  
    //scope = create_scope();
    //push("var_addr", &var_addr)
    float tmp = asm_val;
    tmp = tmp * 0.05;

    //execute(scope, 从private_data中去取相应的数据)
    *(float*)var_addr = tmp;
}


Boolean pretest(const char* bytes_arr, int arr_len)
{
   if (arr_len != 16) return False; 
}
