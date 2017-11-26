#ifndef FILL_PLAIN_STRUCT_H
#define FILL_PLAIN_STRUCT_H

#include "driver_match.h"

// plain_struct相关函数
extern int fill_plain_struct
(
   const char* dts_owner_name, 
   const char* para_list_name, 
   struct struct_member st[], 
   struct_fill_func_ptr do_fill
);

static int do_fill_plain_struct
(
   const void* first_para, 
   int num_para,
   struct struct_member st[], 
   struct_fill_func_ptr do_fill
);

#endif
