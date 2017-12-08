#include "flywheel_match.h"
#include "flywheel.h"
#include "fill_command_sequence.h"
#include "fill_bytes_array_assembly_scheme.h"
#include "collect_code_block.h"
#include <malloc.h>
#include <stdio.h>
#include <string.h>
 
// 数据模板指的是一种类型
// 模板数据指的是某种数据模板类型的具体值


static int global_match_template0(void){ return MATCH; }
static int open_match_template0(void) { return MATCH; }

static int set_speed_match_template0(void)
{
   static struct command_sequence* set_speed_data_template0;
   int exec_status;

   set_speed_data_template0 = malloc(sizeof(struct command_sequence));

   exec_status = fill_command_sequence("flywheel_set_speed", 
                                       "set_speed_template0_data",
                                        set_speed_data_template0);
 
   collect_code_block("flywheel_set_speed",
                      "set_speed_template0_data",
                      "compute",
                       GROUP,
                       set_speed_data_template0->compute_funcs); 
  

   return check_match(exec_status,
                      FLYWHEEL_SET_SPEED_INDEX,
                      0, // template_id 
                      (void*)set_speed_data_template0);
}


static int receive_match_template0(void)
{
    struct bytes_array_assembly_scheme* receive_data_template0;
    int exec_status;

    receive_data_template0 = malloc(sizeof(struct bytes_array_assembly_scheme));

    exec_status = fill_bytes_array_assembly_scheme("flywheel_receive", 
                                                   "receive_template0_data",
                                                    receive_data_template0);
    
    collect_code_block("flywheel_receive",
                       "receive_template0_data",
                       "postprocess",
                        GROUP,
                        receive_data_template0->postprocess_funcs); 

    collect_code_block("flywheel_receive",
                       "receive_template0_data",
                       "precondition",
                        SINGLE,
                        receive_data_template0->precondition); 

    return check_match(exec_status, 
                       FLYWHEEL_RECEIVE_INDEX,
                       0, 
                      (void*)receive_data_template0);
}


// 模板匹配函数表
static struct template_match match_funcs_table[FLYWHEEL_TEMPLATE_NUM] = {
    {"global_template0", global_match_template0},
    {"flywheel_open_template0", open_match_template0},
    {"flywheel_set_speed_template0", set_speed_match_template0},
    {"flywheel_receive_template0", receive_match_template0},
    // 下一个模板号的匹配函数写在下面
}; 


static struct match_info flywheel_match_info = {
   (FLYWHEEL_OP_NUM+1),
   match_funcs_table,
   MATCH_FUNCS_NUM,
   NULL,
   NULL
};


int flywheel_match(void)
{
    return  do_match(&flywheel_match_info);
}
