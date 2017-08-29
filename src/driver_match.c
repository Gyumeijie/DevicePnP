#include "driver_match.h"
#include "xml_operation.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>


/** 
 *　输入：待匹配设备的类型dev_type，处理不匹配的情况的函数undo_match以及通过
 *        模板名查找并执行相对应的模板匹配函数find_and_exec_match_func
 *　输出：匹配是否成功
 *　功能：通用的匹配逻辑
 */
int do_match(struct match_info* mip)
{
    int length;
    char* op_name = NULL;
    int template_id;
    char template_name[MAX_TEMPLATE_NAME_LENGTH];
    int exec_status;

    g_mip = mip;
    
    //初始化设备的模板参数结构体表
    init_template_data_table(mip->data_table_size);

#if 0
    //先通过全局变量匹配函数来匹配以及收集全局的参数信息
    if (!try_match(template_name)) return UNMATCH;
#endif 
    //然后依次匹配以及收集每个模板的参数
    int i;
    length = get_op_list_length();
    for (i=0; i<length; i++){
        op_name = get_op_name();
        template_id = get_op_template_id(op_name);
                
        construct_template_name(template_name, op_name, template_id);
        
        if (!try_match(template_name)) return UNMATCH;
    }

    //返回匹配
    return MATCH;
}


static void construct_template_name(char* template_name, char* op_name, int template_id)
{
    //构造模板名 设备类型_操作名_templatexxx，其中xxx为template_id
     sprintf(template_name, "%s_template%d", op_name, template_id);
}


static int try_match(char* template_name)
{
    int exec_status;

    //通过模板名找到给定模板的匹配函数入口地址并执行
    exec_status = find_and_exec_match_func(template_name);
    if (!exec_status){
        //释放掉匹配以及收集前面模板所分配的数据结构并返回不匹配
        undo_match();
        g_mip->template_data_table = NULL;
    }

    return exec_status;
}

static void init_template_data_table(int dtsize)
{ 
    g_mip->template_data_table = malloc(sizeof(struct template_data)*dtsize); 
#if DEBUG
    printf("template_data_table: %p\n", g_mip->template_data_table);
#endif
}



//释放模板对应的数据结构
static void undo_match(void)
{
    if (g_mip != NULL){
        free(g_mip->template_data_table);
        g_mip->template_data_table = NULL;
    }
}


static int find_and_exec_match_func(char* name)
{

    //查找匹配函数，如果没有找到则返回不匹配，并给出具体的原因
    match_func_ptr match_func = find_match_func(name);

    if (match_func == NULL){
#if DEBUG
        printf("Error: tempalte %s has no corresponding match function\n", name);
#endif
        return UNMATCH;
    }

    //执行函数
    return match_func();
}


/**
 *　输入：模板函数名name
 *　输出：模板函数名name对应的模板的匹配函数
 *　功能：查找模板匹配函数
 */
static match_func_ptr find_match_func(char* name)
{
    int i;
    struct template_match* match_funcs_table;
    int match_funcs_num;
  
    printf("name %s\n", name); 
    match_funcs_num = g_mip->match_funcs_num;
    match_funcs_table = g_mip->match_funcs_table;
    for (i=0; i<match_funcs_num; i++){
        if (strcmp(match_funcs_table[i].name, name) == 0){
            return match_funcs_table[i].match_func;
        }
    }

    //否则没有给定的模板,返回NULL
    return NULL;
}


extern int check_match(int status, int index, int template_id, void* template_data)
{
    struct template_data* template_data_table;
    template_data_table = g_mip->template_data_table; 
    
    //返回不匹配
    if (!status) return UNMATCH;

    //否则将收集到的数据存放到template_data_table中供后面使用
    template_data_table[index].para_struct = template_data;
    template_data_table[index].template_id = template_id;
    
    //返回匹配
    return MATCH;
}


void* get_template_data_table(void)
{
    return (void*)g_mip->template_data_table;
}


struct match_info*
init_match_info(struct template_match* match_funcs_table, int data_table_size, int match_funcs_num)
{
    struct match_info* mip;

    mip = (struct match_info*)malloc(sizeof(struct match_info));
    mip->template_data_table = NULL;
    mip->match_funcs_table = match_funcs_table;
    mip->data_table_size = data_table_size;
    mip->match_funcs_num = match_funcs_num;

    return mip;
}
