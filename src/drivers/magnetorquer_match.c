#include "magnetorquer_match.h"
#include "magnetorquer.h"
#include "fill_plain_array.h"
#include "error_report.h"
#include <malloc.h>
#include <stdio.h>
#include <string.h>

/*
 * 对于ad设备的magnetorquer而言没有全局的信息要收集以及设备打开操作并没有
 * 实质性的操作；在这里写是为了防止用户在配置信息的时候将global以及op为open写
 * 上而没有相应的匹配函数出错
 */

static int global_match_template0(void){ return MATCH; }
static int open_match_template0(void) { return MATCH; }

static int setx_match_template0(void)
{
   return set_pat0_match("magnetorquer_setx",
                         "setx_template0_data",
                         MAGNETORQUER_SETX_INDEX); 
}

static int sety_match_template0(void)
{
   return set_pat0_match("magnetorquer_sety",
                         "sety_template0_data",
                         MAGNETORQUER_SETY_INDEX); 
}


static int setz_match_template0(void)
{
   return set_pat0_match("magnetorquer_setz",
                         "setz_template0_data",
                         MAGNETORQUER_SETZ_INDEX); 
}


static int setxyz_match_template0(void)
{
   return set_pat0_match("magnetorquer_setxyz",
                         "setxyz_template0_data",
                         MAGNETORQUER_SETXYZ_INDEX); 
}


// 辅助函数
static int set_pat0_match(char* op_name, char* para_name, int op_idx)
{
   struct plain_array* set_data_template0 = malloc(sizeof(struct plain_array));
   check_malloc(set_data_template0);
   set_data_template0->type = "int"; 

   int exec_status;
   exec_status = fill_plain_array(op_name, para_name, set_data_template0); 

   return check_match(exec_status, op_idx, 0, (void*)set_data_template0);
}


// 模板匹配函数表
static struct template_match match_funcs_table[MAGNETORQUER_TEMPLATE_NUM] = {
   {"global_template0", global_match_template0},
   {"magnetorquer_open_template0", open_match_template0},
   {"magnetorquer_setx_template0", setx_match_template0},
   {"magnetorquer_sety_template0", sety_match_template0},
   {"magnetorquer_setz_template0", setz_match_template0},
   {"magnetorquer_setxyz_template0", setxyz_match_template0}
}; 


static struct match_info magnetorquer_match_info = {
   (MAGNETORQUER_OP_NUM+1),
   match_funcs_table,
   MATCH_FUNCS_NUM,
   NULL,
   NULL
};


int magnetorquer_match(void)
{
    return  do_match(&magnetorquer_match_info);
}
