#ifndef BYTES_ARRAY_ASSEMBLY_H
#define BYTES_ARRAY_ASSEMBLY_H

#include "driver_match.h"
#include "parameter_package.h"

#define NO_NEED_POSTPROCESSION -1

extern int do_bytes_array_assembly
(
   const char* bytes_arr,                          //接受到的字节数组
   int arr_len,                                 
   struct parameter_package* para_pkgp,            //字节装配后的值存放的位置
   struct bytes_array_assembly_scheme* asm_schemep //字节装配方案
);

extern int assembly_item(const char* bytes_arr, int arr_len);

static void postprocess_parameter
(
   struct parameter* para,
   struct group_code_blocks* gcb,
   const char* bytes_arr,
   int asm_val,  
   int postprocess_id
);


static int do_check_precondition
(
   struct single_code_block* precondition,
   int arr_len,
   const char* bytes_arr
);


static Boolean is_precondition_failed
(
   struct single_code_block* precondition,
   int arr_len,
   const char* bytes_arr
);

static void do_postprocession
(
   struct group_code_blocks* gcb,
   int postprocess_id,
   int asm_val,
   const char* bytes_arr,
   void* var_addr
);


static Boolean need_postprocess
(
   struct group_code_blocks* postprocess_funcs,
   int postprocess_id
);


static int check_bytes_num();

#endif 
