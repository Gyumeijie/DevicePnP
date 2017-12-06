#include "magnetometer_match.h"
#include "magnetometer.h"
#include "fill_plain_array.h"
#include <malloc.h>
#include <stdio.h>
#include <string.h>

/*
 * 对于ad设备的magnetometer而言没有全局的信息要收集以及设备打开操作并没有
 * 实质性的操作；在这里写是为了防止用户在配置信息的时候将global以及op为open写
 * 上而没有相应的匹配函数出错
 */

static int global_match(void){ return MATCH; }
static int open_match_template0(void) { return MATCH; }

static int getx_match_template0(void)
{
   return get_pat0_match("magnetometer_getx",
                         "tdm0",
                         MAGNETOMETER_GETX_INDEX);
}


static int gety_match_template0(void)
{
   return get_pat0_match("magnetometer_gety",
                         "tdm0",
                         MAGNETOMETER_GETY_INDEX);
}


static int getz_match_template0(void)
{
   return get_pat0_match("magnetometer_getz",
                         "tdm0",
                         MAGNETOMETER_GETZ_INDEX);
}


static int getxyz_match_template0(void)
{
   return get_pat0_match("magnetometer_getxyz",
                         "tdm0",
                         MAGNETOMETER_GETXYZ_INDEX);
}


// 辅助函数
static int get_pat0_match(char* op_name, char* para_name, int op_idx)
{
    struct plain_array* get_data_template0;
    int exec_status;

    get_data_template0  = malloc(sizeof(struct plain_array));
    get_data_template0->type = "int"; 

    exec_status = fill_plain_array(op_name, para_name, get_data_template0); 

    return check_match(exec_status, op_idx, 0, (void*)get_data_template0);
}


// 模板匹配函数表
static struct template_match match_funcs_table[MAGNETOMETER_TEMPLATE_NUM] = {
    {"global", global_match},
    {"magnetometer_open_template0", open_match_template0},
    {"magnetometer_getx_template0", getx_match_template0},
    {"magnetometer_gety_template0", gety_match_template0},
    {"magnetometer_getz_template0", getz_match_template0},
    {"magnetometer_getxyz_template0", getxyz_match_template0}
}; 


static struct match_info magnetometer_match_info = {
   (MAGNETOMETER_OP_NUM+1),
   match_funcs_table,
   MATCH_FUNCS_NUM,
   NULL,
   NULL
};


int magnetometer_match(void)
{
    return  do_match(&magnetometer_match_info);
}
