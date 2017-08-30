#include "analogsunsensor_match.h"
#include "xml_operation.h"
#include <malloc.h>
#include <stdio.h>
#include <string.h>

static int open_template0_match(void) 
{
   return MATCH;
}

static int read_template0_match(void) 
{

    int exec_status;

    //分配open_template0结构体
    read_template0  = (struct plain_array*)malloc(sizeof(struct plain_array));
    read_template0->type = "int"; 

    //获取信息
    exec_status = fill_plain_array("analogsunsensor_read","read_template0", read_template0); 

    //返回不匹配或者匹配
    return check_match(exec_status, ANALOGSUNSENSOR_READ_INDEX, 0, (void*)read_template0);
}



//模板匹配函数表
static struct template_match match_funcs_table[ANALOGSUNSENSOR_TEMPLATE_NUM] = {
    {"analogsunsensor_open_template0", open_template0_match},
    {"analogsunsensor_read_template0", read_template0_match},
}; 
static int match_funcs_num = 2;


extern int analogsunsensor_match(void)
{
    struct match_info* mip;
    mip = init_match_info(match_funcs_table, (ANALOGSUNSENSOR_OP_NUM+1), match_funcs_num);

    return  do_match(mip);
}
