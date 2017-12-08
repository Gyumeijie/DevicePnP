#include "analogsunsensor_match.h"
#include "analogsunsensor.h"
#include "fill_plain_array.h"
#include <malloc.h>
#include <stdio.h>
#include <string.h>

/*
 * 对于ad设备的analogsunsensor而言没有全局的信息要收集以及设备打开操作并没有
 * 实质性的操作；在这里写是为了防止用户在配置信息的时候将global以及op为open写
 * 上而没有相应的匹配函数出错
 */

static int global_match(void){ return MATCH; }
static int open_match_template0(void) { return MATCH; }

static int read_match_template0(void) 
{
    static struct plain_array* read_data_template0;
    int exec_status;

    read_data_template0  = malloc(sizeof(struct plain_array));
    read_data_template0->type = "int"; 

    exec_status = fill_plain_array("analogsunsensor_read",
                                   "read_template0_data",
                                   read_data_template0); 

    return check_match(exec_status, 
                       ANALOGSUNSENSOR_READ_INDEX,
                       0, // template_id
                       (void*)read_data_template0);
}


// 模板匹配函数表
static struct template_match match_funcs_table[ANALOGSUNSENSOR_TEMPLATE_NUM] = {
    {"global", global_match},
    {"analogsunsensor_open_template0", open_match_template0},
    {"analogsunsensor_read_template0", read_match_template0},
}; 


static struct match_info analongsunsensor_match_info = {
   (ANALOGSUNSENSOR_OP_NUM+1),
   match_funcs_table,
   MATCH_FUNCS_NUM,
   NULL,
   NULL
};


int analogsunsensor_match(void)
{
    return  do_match(&analongsunsensor_match_info);
}
