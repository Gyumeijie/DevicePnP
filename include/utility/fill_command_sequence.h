#ifndef FILL_COMMAND_SEQUENCE_H
#define FILL_COMMAND_SEQUENCE_H

#include <mxml.h>
#include "driver_match.h"

//command_sequence相关函数
extern int fill_command_sequence
(
    char* global_or_op_name,
    char* para_name,
    struct command_sequence* cmd_seqp
);

static int get_cmd_seq_size(int len, mxml_node_t* para);

static int alloc_cmd_seq(int bytes_size, struct command_sequence** cmd_seq2p);

static int do_fill_cmd_seq
( 
   mxml_node_t* para, 
   int len, 
   struct command_sequence** cmd_seq2p
);

#endif
