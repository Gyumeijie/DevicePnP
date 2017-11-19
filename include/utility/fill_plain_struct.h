#ifndef FILL_PLAIN_STRUCT_H
#define FILL_PLAIN_STRUCT_H

#include <mxml.h>
#include "driver_match.h"


//plain_struct相关函数
extern int fill_plain_struct
(
   char* global_or_op_name, 
   char* para_name, 
   struct struct_member st[], 
   struct_fill_func_ptr do_fill
);

static int do_fill_plain_struct
(
   mxml_node_t* first_para, 
   int len,
   struct struct_member st[], 
   struct_fill_func_ptr do_fill
);

#endif
