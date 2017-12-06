#ifndef FILL_PLAIN_ARRAY_H
#define FILL_PLAIN_ARRAY_H

#include "driver_match.h"

// plain_array相关函数
extern int fill_plain_array
(
   const char* template_data_owner_name, 
   const char* template_data_name, 
   struct plain_array* plainap
);

static int alloc_plain_array(int len, struct plain_array** plaina2p);

static int do_fill_plain_array
(
   const void* first_para, 
   int num_para, 
   struct plain_array** plaina2p
);


static void store_data_in_array
(
   void* array, 
   int idx, 
   void* elem, 
   const char* elem_type
);

#endif 
