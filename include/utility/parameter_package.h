#ifndef PARAMETER_PACKAGE_H
#define PARAMETER_PACKAGE_H
 
#include "types.h"

#define SET_BIT(pos, data) (data |= (1<<(pos)))
#define IS_BIT_SET(pos, data) ((data>>(pos)) & 0x01) 

#define PUT_WITHOUT_POS 0
#define PUT_WITH_POS 1

#define TO_INT(src)  (*((int*)(src)))
#define TO_SHORT_INT(src)  (*((short int*)(src)))
#define TO_CHAR(src)  (*((char*)(src)))
#define TO_FLOAT(src)  (*((float*)(src)))

// 在填充参数包的时候需要给出放置参数的位置信息，如果策略是不带位置
// 信息的则传递给fill_parameter_package的put_pos数值应该是没有意义的
// 仅仅是需要传递这样一个参数而已
#define MEANINGLESS_PUT_POS 32

// 这里的value类型为int，仅仅将其作为一个4个字节储存空间；这里不用
// 一个4字节长度的字符数组或者是float是因为int类型的参数占多数，
// 这样可以减少类型转换的次数
// TODO 如果要使用double的话，还是要用char value[8]来进行存储
struct parameter{
   int value; 
   const char* para_type; 
   Boolean is_pointer;
};

// 注意：由于put_tracer在使用位置的放置策略的时候起位图作用，每一位代
// 表一个参数因此最多放置的参数个数是32，实际情况下应该够用
struct parameter_package{
  int num_para;       //容量
  int put_strategy;
  int put_tracer;     //用于跟踪put操作(累加器或者位图 tracer更抽象一点)
  int fetch_tracer;   //用于跟踪fetch操作 
  struct parameter* paras;
};

extern int put_literal
(
    struct parameter_package* para_pkgp, 
    const void* value,
    const char* type
);

extern int put_value
( 
    struct parameter_package* para_pkgp,
    const void* value, 
    const char* type
);

extern int put_literal_with_pos
(
   int put_pos,
   struct parameter_package* para_pkgp,
   const void* value,
   const char* type
);

extern int put_value_with_pos
(
   int put_pos, 
   struct parameter_package* para_pkgp, 
   const void* value,
   const char* type
);

extern int put_address
(
   struct parameter_package* para_pkgp,
   const void* var_addr,
   const char* type
);

extern int put_address_with_pos
(
   int put_pos,
   struct parameter_package* para_pkgp, 
   const void* var_addr,
   const char* type
);

extern struct parameter_package* init_parameter_package
(
   int num_para, 
   int put_strategy
);

extern void destroy_parameter_package(struct parameter_package* para_pkgp);

extern void reset_parameter_package(struct parameter_package* para_pkgp);

extern void reuse_parameter_package(struct parameter_package* para_pkgp);

extern Boolean is_all_parameter_set(struct parameter_package* para_pkgp);

extern struct parameter* fetch_para(struct parameter_package* para_pkgp);

extern void store_data
(
    const void* dest, 
    const void* src, 
    const char* dest_type,
    const char* src_type
);

static void store_floattype_data_from
(
    const char* src_type, 
    const void* dest,
    const void* src
);


static void store_chartype_data_from
(
    const char* src_type, 
    const void* dest,
    const void* src
);


static void store_int16type_data_from
(
    const char* src_type, 
    const void* dest,
    const void* src
);


static void store_int32type_data_from
(
    const char* src_type, 
    const void* dest,
    const void* src
);


static int fill_parameter_package
(  
   struct parameter_package* para_pkgp,
   const void* value, 
   const char* type, 
   int put_strategy,
   int put_pos,
   Boolean is_stored_as_address
);

static Boolean can_not_put
(
   struct parameter_package* para_pkgp, 
   int put_pos, 
   int put_strategy
);

static void update_put_tracer
( 
   struct parameter_package* para_pkgp, 
   int put_strategy,
   int put_pos
);


#endif
