#include "magnetometer_match.h"
#include "magnetometer.h"
#include "fill_plain_array.h"
//#include "config_info_collect.h"
#include <malloc.h>
#include <stdio.h>
#include <string.h>

/*
 * 对于ad设备的magnetometer而言没有全局的信息要收集以及设备打开操作并没有
 * 实质性的操作；在这里写是为了防止用户在配置信息的时候将global以及op为open写
 * 上而没有相应的匹配函数出错
 */
static int global_match(void){ return MATCH; }
static int open_template0_match(void) { return MATCH; }


static int getx_template0_match(void)
{
   return get_pat0_match(MAGNETOMETER_GETX_INDEX, "magnetometer_getx",
                         "getx_template0");   
}

static int gety_template0_match(void)
{
   return get_pat0_match(MAGNETOMETER_GETY_INDEX, "magnetometer_gety",
                         "gety_template0");   
}


static int getz_template0_match(void)
{
   return get_pat0_match(MAGNETOMETER_GETZ_INDEX, "magnetometer_getz",
                         "getz_template0");   
}


static int getxyz_template0_match(void)
{
   return get_pat0_match(MAGNETOMETER_GETXYZ_INDEX, "magnetometer_getxyz",
                         "getxyz_template0");   
}


static int get_pat0_match(int op_idx, char* op_name, char* para_name) 
{
    int exec_status;
    struct plain_array* get_pat0p;

    //分配open_template0结构体
    get_pat0p  = (struct plain_array*)malloc(sizeof(struct plain_array));
    get_pat0p->type = "int"; 

    //获取信息
    exec_status = fill_plain_array(op_name, para_name, get_pat0p); 

    //返回不匹配或者匹配
    return check_match(exec_status, op_idx, 0, (void*)get_pat0p);
}


//模板匹配函数表
static struct template_match match_funcs_table[MAGNETOMETER_TEMPLATE_NUM] = {
    {"global", global_match},
    {"magnetometer_open_template0", open_template0_match},
    {"magnetometer_getx_template0", getx_template0_match},
    {"magnetometer_gety_template0", gety_template0_match},
    {"magnetometer_getz_template0", getz_template0_match},
    {"magnetometer_getxyz_template0", getxyz_template0_match}
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
