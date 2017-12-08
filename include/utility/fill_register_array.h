#ifndef FILL_REGISTER_ARRAY_H
#define FILL_REGISTER_ARRAY_H

#include "driver_match.h"

// register_array相关函数
extern int fill_register_array
(
   const char* template_data_owner_name, 
   const char* template_data_name, 
   struct register_array* regap
);

static int alloc_register_array(int len, struct register_array** rega2p);

static int do_fill_register_array
(
   const void* fisrt_para, 
   int len, 
   struct register_array** rega2p
);

#endif
