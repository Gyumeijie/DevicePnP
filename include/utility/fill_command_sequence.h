#ifndef FILL_COMMAND_SEQUENCE_H
#define FILL_COMMAND_SEQUENCE_H

#include "driver_match.h"

// command_sequence相关函数
extern int fill_command_sequence
(
   const char* template_data_owner_name, 
   const char* template_data_name,
   struct command_sequence* cmd_seqp,
   int* does_need_to_collect_code_block,
   struct code_block_ids_designated* compute_ids_record
 );

static int get_cmd_seq_size(int len, void* para);

static void alloc_cmd_seq(int bytes_size, struct command_sequence** cmd_seq2p);

static int do_fill_cmd_seq
( 
   void* para, 
   int len, 
   struct command_sequence** cmd_seq2p,
   int* does_need_to_collect_code_block,
   struct code_block_ids_designated* compute_ids_record
);


#endif
