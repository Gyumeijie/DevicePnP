#ifndef FILL_BYTES_ARRAY_ASSEMBLY_SCHEME_H
#define FILL_BYTES_ARRAY_ASSEMBLY_SCHEME_H

#include <mxml.h>
#include "driver_match.h"


//bytes_assembly相关函数
extern int fill_bytes_array_assembly_scheme
(
  char* global_or_op_name, 
  char* para_name,
  struct bytes_array_assembly_scheme* asm_schemep
);

static int alloc_bytes_array_assembly_scheme
(
   int num_para, 
   struct bytes_array_assembly_scheme** asm_scheme2p
);

static int do_fill_bytes_array_assembly_scheme
(
  mxml_node_t* para,
  int num_para, 
  struct bytes_array_assembly_scheme** asm_scheme2p
);

#endif
