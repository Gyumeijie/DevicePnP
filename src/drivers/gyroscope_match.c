#include "gyroscope_match.h"
#include "xml_operation.h"
#include "error_report.h"
#include <malloc.h>
#include <string.h>
#include <stdio.h>


static int global_match(void)
{
    int exec_status;

    gyro_globalp = malloc(sizeof(struct gyroscope_global));
    exec_status = fill_plain_struct("global", "global", &gyro_global[0],
                                                         gyro_global_do_fill);

    complementation_record |= 1<<GYROSCOPE_GLOBAL_INDEX;

    return check_match(exec_status, GYROSCOPE_GLOBAL_INDEX, 0,
                                    (void*)gyro_globalp);
}


static int open_template0_match(void)
{
    int exec_status;
    struct reg_array* open_template0;

    //分配open_template0结构体
    open_template0  = (struct reg_array*)malloc(sizeof(struct reg_array));
    
    //获取信息
    exec_status = fill_reg_array("gyroscope_open","open_template0",
                                                   open_template0); 

    complementation_record |= 1<<GYROSCOPE_OPEN_INDEX;

    //返回不匹配或者匹配
    return check_match(exec_status, GYROSCOPE_OPEN_INDEX, 0, 
                                    (void*)open_template0);
}


static int getx_template0_match(void)
{
    return getreg_pat0_match("gyroscope_getx", "getx_template0", 
                                                GYROSCOPE_GETX_INDEX);
}


static int gety_template0_match(void)
{
    return getreg_pat0_match("gyroscope_gety", "gety_template0", 
                                               GYROSCOPE_GETY_INDEX);
}

static int getz_template0_match(void)
{
    return getreg_pat0_match("gyroscope_getz", "getz_template0",
                                                GYROSCOPE_GETZ_INDEX);
}


static int getxyz_template0_match(void)
{
    return getreg_pat0_match("gyroscope_getxyz", "getxyz_template0",
                                                  GYROSCOPE_GETXYZ_INDEX);
}


static int getreg_pat0_match(char* op_name, char* para_name, int index)
{
    int exec_status;

    //分配get_reg_pattern0结构体
    getreg_pat0p = malloc(sizeof(struct get_reg_pattern0));
   
    exec_status = fill_plain_struct(op_name, para_name, &getreg_pat0[0],
                                                         getreg_pat0_do_fill);

    //返回不匹配或者匹配
    return check_match(exec_status, index, 0, (void*)getreg_pat0p);
}


static void gyro_global_do_fill(int index, void* data)
{
    switch(index){
        case 0: 
               gyro_globalp->slave_address = *(char*)data;
               break;
        default:
               break;
    }
}


static void getreg_pat0_do_fill(int index, void* data)
{
     switch(index){
         case 0:
                getreg_pat0p->reg_address = *(char*)data; 
                break;
         case 1:  
                getreg_pat0p->size = *(int*)data; 
                break;
         default:
                break;
     }
}


//模板匹配函数表
static struct template_match match_funcs_table[GYROSCOPE_TEMPLATE_NUM] = {
    {"global", global_match},
    {"gyroscope_open_template0", open_template0_match},
    {"gyroscope_getx_template0", getx_template0_match},
    {"gyroscope_gety_template0", gety_template0_match},
    {"gyroscope_getz_template0", getz_template0_match},
    {"gyroscope_getxyz_template0", getxyz_template0_match}
}; 

static struct match_info gyro_match_info = {
   (GYROSCOPE_OP_NUM+1),
   match_funcs_table,
   MATCH_FUNCS_NUM,
   &gyro_mfs,
   &complementation_record
};


//根据lid唯一标识的的设备配置信息去匹配
int gyroscope_match(void)
{  
    return  do_match(&gyro_match_info);
}


