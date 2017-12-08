#include "gyroscope_match.h"
#include "gyroscope_match.h"
#include "fill_plain_struct.h"
#include "fill_register_array.h"
#include "error_report.h"
#include <malloc.h>
#include <string.h>
#include <stdio.h>


static int global_match(void)
{
    int exec_status;

    global_data_template0 = malloc(sizeof(struct gyroscope_global));
    exec_status = fill_plain_struct("global", 
                                    "global_template0_data", 
                                     &gyro_global[0],
                                     gyro_global_do_fill);

    complementation_record |= 1<<GYROSCOPE_GLOBAL_INDEX;

    return check_match(exec_status, 
                       GYROSCOPE_GLOBAL_INDEX,
                       0,
                       (void*)global_data_template0);
}


static int open_match_template0(void)
{
    struct register_array* open_data_template0;
    int exec_status;

    open_data_template0  = malloc(sizeof(struct register_array));
    
    exec_status = fill_register_array("gyroscope_open",
                                      "open_template0_data", 
                                      open_data_template0); 

    complementation_record |= 1<<GYROSCOPE_OPEN_INDEX;

    return check_match(exec_status,
                       GYROSCOPE_OPEN_INDEX,
                       0, 
                       (void*)open_data_template0);
}


static int getx_match_template0(void)
{
    return getreg_pat0_match("gyroscope_getx",
                             "getx_template0_data", 
                             GYROSCOPE_GETX_INDEX);
}


static int gety_match_template0(void)
{
    return getreg_pat0_match("gyroscope_gety", 
                             "gety_template0_data", 
                             GYROSCOPE_GETY_INDEX);
}


static int getz_match_template0(void)
{
    return getreg_pat0_match("gyroscope_getz", 
                             "getz_template0_data", 
                             GYROSCOPE_GETZ_INDEX);
}


static int getxyz_match_template0(void)
{
    return getreg_pat0_match("gyroscope_getxyz",
                             "getxyz_template0_data", 
                             GYROSCOPE_GETXYZ_INDEX);
}

// 辅助函数
static int getreg_pat0_match(char* op_name, char* para_name, int op_idx)
{
    int exec_status;

    get_data_template0 = malloc(sizeof(struct get_reg_pattern0));
   
    exec_status = fill_plain_struct(op_name,
                                    para_name, 
                                    &getreg_pat0[0],
                                    getreg_pat0_do_fill);

    return check_match(exec_status, op_idx, 0, (void*)get_data_template0);
}


// 结构体成员填充
static void gyro_global_do_fill(int index, void* data)
{
    switch(index){
        case 0: 
               global_data_template0->slave_address = *(char*)data;
               break;
        default:
               break;
    }
}


// 结构体成员填充
static void getreg_pat0_do_fill(int index, void* data)
{
     switch(index){
         case 0:
                get_data_template0->reg_address = *(char*)data; 
                break;
         case 1:  
                get_data_template0->size = *(int*)data; 
                break;
         default:
                break;
     }
}


// 模板匹配函数表
static struct template_match match_funcs_table[GYROSCOPE_TEMPLATE_NUM] = {
    {"global", global_match},
    {"gyroscope_open_template0", open_match_template0},
    {"gyroscope_getx_template0", getx_match_template0},
    {"gyroscope_gety_template0", gety_match_template0},
    {"gyroscope_getz_template0", getz_match_template0},
    {"gyroscope_getxyz_template0", getxyz_match_template0}
}; 

static struct match_info gyro_match_info = {
   (GYROSCOPE_OP_NUM+1),
   match_funcs_table,
   MATCH_FUNCS_NUM,
   &gyro_mfs,
   &complementation_record
};


int gyroscope_match(void)
{  
    return  do_match(&gyro_match_info);
}
