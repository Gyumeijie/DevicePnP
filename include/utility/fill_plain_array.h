#ifndef FILL_PLAIN_ARRAY_H
#define FILL_PLAIN_ARRAY_H

#include <mxml.h>
#include "driver_match.h"


//plain_array相关函数
extern int fill_plain_array
(
  char* global_or_op_name,
  char* para_name, 
  struct plain_array* plainap
);


static int alloc_plain_array(int len, struct plain_array** plaina2p);

static int do_fill_plain_array
(
   mxml_node_t* para, 
   int len, 
   struct plain_array** plaina2p
);

#endif 
