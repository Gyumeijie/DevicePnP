#ifndef FILL_REG_ARRAY_H
#define FILL_REG_ARRAY_H

#include <mxml.h>
#include "driver_match.h"

//reg_array相关函数
extern int fill_reg_array
(
  char* global_or_op_name,
  char* para_name, 
  struct reg_array* regap
);

static int alloc_reg_array(int len, struct reg_array** rega2p);

static int do_fill_reg_array
(
  mxml_node_t* para, 
  int len, 
  struct reg_array** rega2p
);

#endif
