#ifndef FILL_PLAIN_STRUCT_H
#define FILL_PLAIN_STRUCT_H

#include "driver_match.h"

extern int fill_plain_struct
(
   const char* dts_owner_name, 
   const char* para_list_name, 
   struct struct_member st[], 
   fill_struct_function do_fill
);

static int do_fill_plain_struct
(
   const void* first_para, 
   int num_para,
   struct struct_member st[], 
   fill_struct_function do_fill
);

#endif
