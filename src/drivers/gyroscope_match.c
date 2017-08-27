#include "gyroscope_match.h"
#include "xml_operation.h"
#include <malloc.h>
#include <string.h>
#include <stdio.h>


static int open_template0_match(void)
{
    int exec_status;
    
    //分配open_template0结构体
    open_template0  = (struct reg_array*)malloc(sizeof(struct reg_array));
    
    //获取信息
    exec_status = fill_reg_array("gyroscope_open","open_template0", open_template0); 

    //返回不匹配或者匹配
    return check_match(exec_status, GYROSCOPE_OPEN_INDEX, 0, (void*)open_template0);
}


static int getx_template0_match(void)
{
    int exec_status;
    struct getx_template0* getx_tpl0; 
    struct st_member st[2] = {
       {"char", "reg_address", 0},
       {"int", "size", 1}
    };

    //分配getx_template0结构体
    getx_tpl0p  = (struct getx_template0*)malloc(sizeof(struct getx_template0));
   
    exec_status = fill_plain_struct("gyroscope_getx", "getx_template0", 
                                                    &st[0], getxtpl0_do_fill);

    //返回不匹配或者匹配
    return check_match(exec_status, GYROSCOPE_GETX_INDEX, 0, (void*)getx_tpl0p);
}

static void getxtpl0_do_fill(int index, void* data)
{

     switch(index){
         case 0:
                getx_tpl0p->reg_address = *(char*)data; 
                break;
         case 1:  
                getx_tpl0p->size = *(int*)data; 
                break;
         default:
                break;
     }
}




//模板匹配函数表
static struct template_match match_funcs_table[GYROSCOPE_TEMPLATE_NUM] = {
//    {"gyroscope_global", global_match},
    {"gyroscope_open_template0", open_template0_match},
    {"gyroscope_getx_template0", getx_template0_match},
}; 
static int match_funcs_num = 2;



//根据lid唯一标识的的设备配置信息去匹配
extern int gyroscope_match(void)
{  
    struct match_info* mip;
    mip = (struct match_info*)malloc(sizeof(struct match_info));
    mip->template_data_table = NULL;
    mip->match_funcs_table = match_funcs_table;
    mip->data_table_size = (GYROSCOPE_OP_NUM+1);
    mip->match_funcs_num = match_funcs_num;

    return  do_match(mip);
}
