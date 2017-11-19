#ifndef COMMAND_SEQUENCE_FILL_H
#define COMMAND_SEQUENCE_FILL_H

#include "parameter_package.h"
#include "driver_match.h"
#include "types.h"

#define MAX_COMPUTE_FUNCTION_NUM  32
#define PRESET_COMPUTE_FUNCTION_NUM 1

#define SET_BITS(pos) ((1<<(pos)) - 1)
#define SET_BIT(pos, data) (data |= (1<<(pos)))
#define CLEAR_BIT(pos, data) (data &= (data - (1<<(pos))))
#define IS_BIT_SET(pos, data) ((data>>(pos)) & 0x01) 


typedef void (*compute_func)(char*, int, void*);

struct compute_functions_manager{
  int funcs_bitmap;
  compute_func* compute_funcs_arr;
};


extern void fill_cmd_seq_dynamically(struct command_sequence* cmd_seqp, 
                                     struct parameter_package* para_packp);

static void dispatch_by_compute_id(int compute_id, char* bytes_value, 
                                   int size, void* para);

extern void use_compute_func(int func_id, char* bytes_value, int size, void* para);

extern int register_compute_func(int compute_id, compute_func func);

extern void unregister_compute_func(int compute_id);

static Boolean has_func_registered(int compute_id);

static Boolean is_bad_compute_id(int compute_id);

extern void inspect_compute_funcs_bitmap(int column);

static void calculate_checksum(char* bytes_value, int size);


//预先定义的计算函数
static void compute_func0(char* bytes_value, int size, void* para);


#endif
