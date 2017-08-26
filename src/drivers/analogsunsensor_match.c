#include "analogsunsensor_match.h"
#include "xml_operation.h"
#include <malloc.h>
#include <stdio.h>

static int open_template0_match(void) 
{
   return 1;
}

static int read_template0_match(void) 
{

    int exec_status;

    //分配open_template0结构体
    read_template0  = (struct plain_array*)malloc(sizeof(struct plain_array));
    
    //获取信息
    exec_status = fill_plain_array("analogsunsensor_read","read_template0", read_template0); 

    //返回不匹配或者匹配
    return check_match(exec_status, ANALOGSUNSENSOR_READ_INDEX, 0, (void*)read_template0);
}



static int check_match(int status, int index, int template_id, void* template_data)
{
    //返回不匹配
    if (status == 0) return 0;

    //否则将收集到的数据存放到template_data_table中供后面使用
    template_data_table[index].para_struct = template_data;
    template_data_table[index].template_id = template_id;
    
    //返回匹配
    return 1;
}


//模板匹配函数表
static struct template_match match_funcs_table[ANALOGSUNSENSOR_TEMPLATE_NUM] = {
    {"analogsunsensor_open_template0", open_template0_match},
    {"analogsunsensor_read_template0", read_template0_match},
}; 
static int match_funcs_num = 2;


/**
 *　输入：模板函数名name
 *　输出：模板函数名name对应的模板的匹配函数
 *　功能：查找模板匹配函数
 */
static match_func_ptr find_match_func(char* name)
{
    int i;
    for (i=0; i<match_funcs_num; i++){
        if (strcmp(match_funcs_table[i].name, name) == 0){
            return match_funcs_table[i].match_func;
        }
    }

    //否则没有给定的模板,返回NULL
    return NULL;
}

//释放模板对应的数据结构
static void undo_match(void)
{
    //会自动递归释放para结构体?
    free(template_data_table);
    template_data_table = NULL;
}


static int find_and_exec_match_func(char* name)
{

    //查找匹配函数，如果没有找到则返回不匹配，并给出具体的原因
    match_func_ptr match_func = find_match_func(name);
    if (match_func == NULL){
#if DEBUG
        printf("Error: tempalte %s has no corresponding match function\n", name);
#endif
        return 0;
    }

    //执行函数
    return match_func();
}


static void* init_template_data_table(void)
{ 
    template_data_table = malloc(sizeof(struct template_data)*(ANALOGSUNSENSOR_OP_NUM+1));
#if DEBUG
    printf("template_data_table: %p\n", template_data_table);
#endif
    return (void*)template_data_table;
}


extern int analogsunsensor_match(void)
{
    return do_match(init_template_data_table, 
                    find_and_exec_match_func, undo_match);
}
