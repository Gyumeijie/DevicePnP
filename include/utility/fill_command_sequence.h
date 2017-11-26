#ifndef FILL_COMMAND_SEQUENCE_H
#define FILL_COMMAND_SEQUENCE_H

#include "driver_match.h"

// command_sequence相关函数
extern int fill_command_sequence
(
   const char* dts_owner_name, 
   const char* para_list_name,
   struct command_sequence* cmd_seqp
);

static int get_cmd_seq_size(int len, void* para);

static int alloc_cmd_seq(int bytes_size, struct command_sequence** cmd_seq2p);

static int do_fill_cmd_seq
( 
   void* para, 
   int len, 
   struct command_sequence** cmd_seq2p
);

#endif
