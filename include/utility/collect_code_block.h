#ifndef COLLECT_CODE_BLOCK
#define COLLECT_CODE_BLOCK

#include "driver_match.h"

// 代码块的组织方式
enum {SINGLE, GROUP};

extern int collect_code_block
(
   char* op_name,
   char* code_block_name,
   int code_block_mode,
   void* code_block_struct
);

static int do_single_code_block_collection
(
   void* op_context,
   const char* elem_name,
   struct single_code_block* scb
);

static int do_group_code_blocks_collection
(
   void* op_context,
   const char* elem_name,
   struct group_code_blocks* gcb
);

static void install_code_block
(
   const char** code_block_src_array,
   const int length,
   void* code_block
);

#endif 
