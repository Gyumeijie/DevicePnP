#include "flywheel_match.h"
#include "flywheel.h"
#include "fill_command_sequence.h"
#include "fill_bytes_array_assembly_scheme.h"
//#include "config_info_collect.h"
#include <malloc.h>
#include <stdio.h>
#include <string.h>


//将具体的匹配方法分割开来
static int global_match(void){ return MATCH; }
static int open_template0_match(void) { return MATCH; }


//分离的方法有两种一种是:按模板号分(有一整套方案，选择的可能就不太灵活)或者是按接口分
//            另外一种是:按函数名分(粒度更小，可能更灵活)
static int set_speed_template0_match(void) 
{
    int exec_status;

    //分配open_template0结构体
    set_speed_template0 = malloc(sizeof(struct command_sequence));

    //获取信息
    exec_status = fill_command_sequence("flywheel_set_speed", 
                                        "flywheel_set_speed_template0",
                                         set_speed_template0);
    //返回不匹配或者匹配
    return check_match(exec_status, FLYWHEEL_SET_SPEED_INDEX, 0, 
                                    (void*)set_speed_template0);
}


static int receive_template0_match(void)
{
    int exec_status;

    //分配open_template0结构体
    receive_template0 = malloc(sizeof(struct bytes_array_assembly_scheme));

    //获取信息
    exec_status = fill_bytes_array_assembly_scheme("flywheel_receive", 
                                                   "flywheel_receive_template0",
                                                    receive_template0);
    //返回不匹配或者匹配
    return check_match(exec_status, FLYWHEEL_RECEIVE_INDEX, 0, 
                                    (void*)receive_template0);
}

//模板匹配函数表
//作为一个整体存在
static struct template_match match_funcs_table[FLYWHEEL_TEMPLATE_NUM] = {
    {"global", global_match},
    {"flywheel_open_template0", open_template0_match},
    {"flywheel_set_speed_template0", set_speed_template0_match},
    {"flywheel_receive_template0", receive_template0_match},

    //
    //下一个模板号的匹配函数写在下面
    //
    //
    //
}; 


//整体的一个配置
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
