#ifndef COMMAND_SEQUENCE_FILL_H
#define COMMAND_SEQUENCE_FILL_H

#include "parameter_package.h"
#include "driver_match.h"
#include "types.h"


// 如果配置文件中给的compute_id是-1的话，那么这个参数就不需要
// 进行计算了，默认的都是32位无符号整型或者通过转型
#define NO_NEED_COMPUTATION -1

typedef void (*compute_func)(char*, int, void*);

struct compute_functions_manager{
  int funcs_bitmap;
  compute_func* compute_funcs_arr;
};


extern void fill_cmd_seq_dynamically
(
   struct parameter_package* para_packp,
   struct command_sequence* cmd_seqp 
);


static void calculate_checksum(char* bytes_value, int size);

static void split_uint32_into_bytes
(
   char* bytes_value, 
   int size, 
   unsigned int para
);

static void process_parameter
(
   struct parameter* para,
   struct group_code_blocks* compute_funcs,
   int compute_id,
   char* start_addr_to_fill,
   int size
);

static unsigned int cast_to_uint32(struct parameter* para);

static int do_computation
(
   int compute_id,
   struct group_code_blocks* compute_funcs,
   struct parameter* para
);

#endif
