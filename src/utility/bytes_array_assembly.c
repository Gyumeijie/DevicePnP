#include "miscellaneous.h"
#include "driver_match.h"
#include "device.h"
#include "miscellaneous.h"
#include "bytes_array_assembly.h"
#include "types.h"
#include <stdio.h>
#include <malloc.h>


int do_bytes_array_assembly
(
   const char* bytes_arr,                     
   int arr_len,                                
   struct parameter_package* para_pkgp,           
   struct bytes_array_assembly_scheme* asm_schemep 
)
{
  //TODO 检查所需的字节与读取的字节是否相匹配
   if (para_pkgp->num_para != asm_schemep->num_para) return 1;

   int num_para = para_pkgp->num_para;
   printf("num_para: %d\n", num_para);

   //调用先验条件进行判断
   if (! (asm_schemep->precond_func == (precondition_function)0 ||
          asm_schemep->precond_func(bytes_arr, arr_len))){
       return 1;
   }
   
   int i;
   int asm_val;
   struct bytes_assembly_descriptor* descs = asm_schemep->bytes_asm_descs;
   post_process_function* post_proc_funcs = asm_schemep->post_proc_funcs;
   for (i=0; i<num_para; i++){
      struct parameter* parap = fetch_para(para_pkgp);
      void* var_addr = (void*)parap->value;

      //获取位置信息
      int num_byte = descs[i].num_byte;
      int start = descs[i].start;
      asm_val = assembly_item(bytes_arr + start, num_byte); 

      //调用数据的特殊处理函数(对字节组合成的数据进行特殊的处理)
      //两种方案:
      //        1 设置默认的函数,统一进行调用
      //        2 调用之前都要进行是否为NULL的判断
      if (post_proc_funcs[i] != NULL){
          post_proc_funcs[i](bytes_arr + start, num_byte, asm_val, var_addr);
      }else{
          //没有的话就做默认处理,即按照给定的类型进行存储
          store_data(var_addr, &asm_val, parap->para_type, "int");
      }
   }

   return 0;
}


int assembly_item(const char* bytes_arr, int arr_len)
{
    //TODO 检测bytes_arr和arr_len的合法性
    int temp = bytes_arr[0];  

    int i;
    for (i=1; i<arr_len; i++){
        temp = temp << 8;
        temp |= bytes_arr[i];  
    }

    return temp;
}


int register_post_processing_func_for_paras
(
   const char* lid,
   const int op_idx,
   post_process_function post_proc_func, 
   int paras_pos[],
   int arr_len 
)
{
    int i;
    for (i=0; i<arr_len; i++){
       int para_pos = paras_pos[i];
       register_post_processing_func(lid, op_idx, post_proc_func, para_pos);
    }

    return 0;
}


int register_post_processing_func
(
   const char* lid,
   const int op_idx,
   post_process_function post_proc_func, 
   int para_pos
)
{
    //TODO 更细致的检查处理
   struct bytes_array_assembly_scheme* asm_schemep;
   asm_schemep = fetch_assembly_shceme(lid, op_idx); 
   asm_schemep->post_proc_funcs[para_pos] = post_proc_func;

   return 0;
}


int register_precondition_function
(
   const char* lid,
   int op_idx,
   precondition_function precond_func
)
{
   struct bytes_array_assembly_scheme* asm_schemep;
   asm_schemep = fetch_assembly_shceme(lid, op_idx); 
   asm_schemep->precond_func = precond_func;

   return 0;
}


static struct bytes_array_assembly_scheme* fetch_assembly_shceme
(
   const char* lid,
   const int op_idx
)
{
   //TODO 其它的操作的结构不会被损害, 检查每一步查找的结果
   //查找设备
   struct device* devp = find_device(lid);
   //获取模板数据表
   struct template_data* template_data_table = devp->private_data;
   //获取相应操作的数据结构
   struct template_data* op_data = &template_data_table[op_idx];

   return (struct bytes_array_assembly_scheme*)op_data->para_struct;
}


