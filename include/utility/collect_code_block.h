#ifndef COLLECT_CODE_BLOCK
#define COLLECT_CODE_BLOCK

#include "driver_match.h"

#define NO_NEED_CODE_BLOCK -1

// 代码块的组织方式
enum {SINGLE, GROUP};

extern int collect_code_block
(
   const char* op_name,
   const char* template_data_name,
   const char* code_block_name,
   int code_block_mode,
   void** code_block_struct
);


extern void check_code_block_ids_validity
(
   const struct code_block_ids_designated* ids_record,
   int num_code_block
);


static int do_single_code_block_collection
(
   void* template_data_context,
   const char* code_block_name,
   void** code_block_struct
);


static int do_group_code_blocks_collection
(
   void* template_data_context,
   const char* code_block_name,
   void** code_block_struct
);

static int get_code_block_list_length(void* code_block_list);

static void init_group_code_blocks
(
   int num_code_block,
   struct group_code_blocks* gcb
);

static void install_code_block
(
   void* code_block,
   const char** code_block_src_array,
   const int num_code_block
);

#endif 
