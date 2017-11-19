#ifndef BYTES_ARRAY_ASSEMBLY_H
#define BYTES_ARRAY_ASSEMBLY_H

#include "driver_match.h"
//GET 如果没有包含parameter_package.h，下面的会报struct parameter_package
//declared inside parameter list
#include "parameter_package.h"

extern int do_bytes_array_assembly
(
   const char* bytes_arr,                          //接受到的字节数组
   int arr_len,                                 
   struct parameter_package* para_pkgp,            //字节装配后的值存放的位置
   struct bytes_array_assembly_scheme* asm_schemep //字节装配方案
);

extern int assembly_item(const char* bytes_arr, int arr_len);

extern int register_precondition_function
(
   const char* lid,
   int op_idx,
   precondition_function precond_func
);

extern int register_post_processing_func
(
   const char* lid,
   int op_idx,
   post_process_function post_proc_func, 
   int para_pos
);

extern int register_post_processing_func_for_paras
(
   const char* lid,
   int op_idx,
   post_process_function post_proc_func, 
   int paras_pos[],
   int arr_len 
);

static struct bytes_array_assembly_scheme* fetch_assembly_shceme
(
   const char* lid,
   int op_idx
);

static int check_bytes_num();


#endif 
