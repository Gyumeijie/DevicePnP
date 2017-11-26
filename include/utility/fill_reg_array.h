#ifndef FILL_REG_ARRAY_H
#define FILL_REG_ARRAY_H

#include "driver_match.h"

// reg_array相关函数
extern int fill_reg_array
(
  const char* dts_owner_name, 
  const char* para_list_name, 
  struct reg_array* regap
);

static int alloc_reg_array(int len, struct reg_array** rega2p);

static int do_fill_reg_array
(
  const void* fisrt_para, 
  int len, 
  struct reg_array** rega2p
);

#endif
