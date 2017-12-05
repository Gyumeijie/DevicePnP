#include "miscellaneous.h"
#include "driver_match.h"
#include "device.h"
#include "miscellaneous.h"
#include "bytes_array_assembly.h"
#include "interpreter.h"
#include "types.h"
#include "error_report.h"
#include "type_converter.h"
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
   if (para_pkgp->num_para != asm_schemep->num_para) return 1;

   struct group_code_blocks* postprocess_funcs = asm_schemep->postprocess_funcs;
   struct single_code_block* precondition = asm_schemep->precondition;

   // 调用先验条件进行判断
   if (is_precondition_failed(precondition, arr_len, bytes_arr)){
        printf("check failed\n"); 
        return 1;
   }


   int i;
   int num_para = para_pkgp->num_para;
   struct bytes_assembly_descriptor* descs = asm_schemep->bytes_asm_descs;
   for (i=0; i<num_para; i++){
      struct parameter* parap = fetch_para(para_pkgp);

      // 获取位置信息
      int num_byte = descs[i].num_byte;
      int start = descs[i].start;
      int process_id = descs[i].process_id;

      int asm_val = assembly_item(bytes_arr+start, num_byte); 

      postprocess_parameter(parap,
                            postprocess_funcs,
                            bytes_arr,
                            asm_val, 
                            process_id);
  }

   // 重置parameter_package中的fetch_tracer使得下一次可以重新使用
   reuse_parameter_package(para_pkgp);

   return 0;
}


static void postprocess_parameter
(
   struct parameter* para,
   struct group_code_blocks* postprocess_funcs,
   const char* bytes_arr,
   int asm_val,  
   int process_id
)
{
   void* var_addr = (void*)para->value;

   if (need_postprocess(postprocess_funcs, process_id)){
      do_postprocession(postprocess_funcs,
                        process_id,
                        asm_val, 
                        bytes_arr,
                        var_addr);
   }else{
      // 没有的话就做默认处理,即按照给定的类型进行存储
      store_data(var_addr, &asm_val, para->para_type, "int");
    }
}


static Boolean is_precondition_failed
(
   struct single_code_block* precondition,
   int arr_len,
   const char* bytes_arr
 
)
{
   if (! (precondition == NULL || 
         do_check_precondition(precondition, arr_len, bytes_arr)))
   {
      return True; 
   }

   return False;
}


static Boolean need_postprocess
(
   struct group_code_blocks* postprocess_funcs,
   int process_id
)
{
    const char* src = postprocess_funcs->code_block_src_array[process_id];
    if ((process_id > NO_NEED_POSTPROCESSION) && (src != NULL)){
       return True;
    }

    return False;
}


static void do_postprocession
(
   struct group_code_blocks* gcb,
   int process_id,
   int asm_val,
   const char* bytes_arr,
   void* var_addr
)
{
   static int  result;
   static int static_asm_val;
   static int static_var_addr;
   static const char* static_bytes_arr;

   static_asm_val = asm_val;
   static_bytes_arr = bytes_arr;
   static_var_addr = (int)var_addr;
   
   int* code = gcb->compiled_byte_code_array[process_id];

   if (code != NULL){
      run_code(code);
   }else{
       struct dependency_items* dep_items;
       dep_items = init_dependency_items(4);

       add_dependency_item(dep_items, "bytes_arr", &static_bytes_arr, CHAR+PTR);
       add_dependency_item(dep_items, "var_addr", &var_addr, CHAR+PTR);
       add_dependency_item(dep_items, "asm_val", (void*)&static_asm_val, INT);
       add_dependency_item(dep_items, "result", (void*)&result, INT);

        // 根据process_id获取源码数据
        const char* src = gcb->code_block_src_array[process_id];

        // 将编译的代码放在存放在相应的字段中
        code = compile_src_code(dep_items, src);
        gcb->compiled_byte_code_array[process_id] = code;

        run_code(code);
     }
}


static int do_check_precondition
(
   struct single_code_block* precondition,
   int arr_len,
   const char* bytes_arr
)
{
   static int result;
   static int static_arr_len;
   static const char* static_bytes_arr;
   
   static_arr_len = arr_len;
   static_bytes_arr = bytes_arr;

   int* code = precondition->compiled_byte_code;

   if (code != NULL){
       run_code(code);
   }else{
       struct dependency_items* dep_items;
       dep_items = init_dependency_items(3);
       add_dependency_item(dep_items, "arr_len", &static_arr_len, INT);
       add_dependency_item(dep_items, "result", &result, INT);
       add_dependency_item(dep_items, "bytes_arr", &static_bytes_arr, CHAR+PTR);
          
       const char* src = precondition->code_block_src;
       code = compile_src_code(dep_items, src);
       precondition->compiled_byte_code = code;

       run_code(code);
   }

  return result;
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

