#ifndef FILL_BYTES_ARRAY_ASSEMBLY_SCHEME_H
#define FILL_BYTES_ARRAY_ASSEMBLY_SCHEME_H

#include "driver_match.h"

// bytes_assembly相关函数
extern int fill_bytes_array_assembly_scheme
(
   const char* template_data_owner_name, 
   const char* template_data_name, 
   struct bytes_array_assembly_scheme* asm_schemep,
   int* need_to_collect_code_block,
   struct code_block_ids_designated* postprocess_ids_record
);

static void alloc_bytes_array_assembly_scheme
(
   int num_para, 
   struct bytes_array_assembly_scheme** asm_scheme2p
);

static int do_fill_bytes_array_assembly_scheme
(
   const void* first_para,
   int num_para, 
   struct bytes_array_assembly_scheme** asm_scheme2p,
   int* need_to_collect_code_block,
   struct code_block_ids_designated* postprocess_ids_record
);

#endif
