#include "magnetorquer_match.h"
#include "magnetorquer.h"
#include "fill_plain_array.h"
//#include "config_info_collect.h"
#include <malloc.h>
#include <stdio.h>
#include <string.h>

/*
 * 对于ad设备的magnetorquer而言没有全局的信息要收集以及设备打开操作并没有
 * 实质性的操作；在这里写是为了防止用户在配置信息的时候将global以及op为open写
 * 上而没有相应的匹配函数出错
 */
static int global_match(void){ return MATCH; }
static int open_template0_match(void) { return MATCH; }


static int setx_template0_match(void)
{
   return set_pat0_match(MAGNETORQUER_SETX_INDEX, "magnetorquer_setx",
                         "setx_template0");   
}

static int sety_template0_match(void)
{
   return set_pat0_match(MAGNETORQUER_SETY_INDEX, "magnetorquer_sety",
                         "sety_template0");   
}


static int setz_template0_match(void)
{
   return set_pat0_match(MAGNETORQUER_SETZ_INDEX, "magnetorquer_setz",
                         "setz_template0");   
}


static int setxyz_template0_match(void)
{
   return set_pat0_match(MAGNETORQUER_SETXYZ_INDEX, "magnetorquer_setxyz",
                         "setxyz_template0");   
}


static int set_pat0_match(int op_idx, char* op_name, char* para_name) 
{
    int exec_status;
    struct plain_array* set_pat0p;

    //分配set_pat0p结构体
    set_pat0p  = (struct plain_array*)malloc(sizeof(struct plain_array));
    set_pat0p->type = "int"; 

    //获取信息
    exec_status = fill_plain_array(op_name, para_name, set_pat0p); 

    //返回不匹配或者匹配
    return check_match(exec_status, op_idx, 0, (void*)set_pat0p);
}


//模板匹配函数表
static struct template_match match_funcs_table[MAGNETORQUER_TEMPLATE_NUM] = {
    {"global", global_match},
    {"magnetorquer_open_template0", open_template0_match},
    {"magnetorquer_setx_template0", setx_template0_match},
    {"magnetorquer_sety_template0", sety_template0_match},
    {"magnetorquer_setz_template0", setz_template0_match},
    {"magnetorquer_setxyz_template0", setxyz_template0_match}
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
