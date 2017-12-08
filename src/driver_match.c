#include "driver_match.h"
#include "config_info_collect.h"
#include "error_report.h"
#include "miscellaneous.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>

static const char* op_context;
static struct template_data* template_data_table;

int do_match(struct match_info* mip)
{
    
    // 初始化设备的模板参数结构体表
    init_template_data_table(mip->data_table_size);

    if (! tackle_global_configuration(mip)) return UNMATCH;

    // 然后根据配置文件依次匹配以及收集每个模板的参数
    int i;
    int length = get_op_list_length();
    for (i=0; i<length; i++){
        char* op_name = get_op_name();
        int template_id = get_op_template_id(op_name);
        op_context = op_name;
         
        char template_name[MAX_TEMPLATE_NAME_LENGTH];
        construct_template_name(template_name, op_name, template_id);
   
        if (! try_match(template_name, mip)) return UNMATCH;
    }

    
    // 检查通用设备驱动是否定义了最小功能集，如果有则检查配置文件
    // 的配置信息是否涵盖了这个最小功能集
    op_context = NULL;
    if (mip->mfsp != NULL){
       return has_all_required_operations_complemented(mip);
   }

    return MATCH;
}


static int tackle_global_configuration(struct match_info* mip)
{
   if (has_global_config_item()){
     op_context = "global";
     char template_name[MAX_TEMPLATE_NAME_LENGTH];
     int template_id = get_global_template_id();
    
     construct_template_name(template_name, "global", template_id);

     if (! try_match(template_name, mip)) return UNMATCH;
    }

    return MATCH;
}


static void construct_template_name
(
   char* template_name,
   char* name,
   int template_id
)
{
    // 构造模板名 设备类型_操作名或global_templatexxx，其中xxx为template_id
    sprintf(template_name, "%s_template%d", name, template_id);
}


static int try_match
(
   char* template_name,
   struct match_info* mip 
)
{
    // 查找匹配函数，如果没有找到则返回不匹配，并给出具体的原因
    match_function match_func = find_match_function(template_name, mip);
    if (! check_null(__FILE__, __func__, "match_func", match_func)){
        printf("Detail: can't not find matching function of template '%s'\n",
                                                            template_name);
        return UNMATCH;
    }

    int exec_status = match_func();
    if (! exec_status){
        // 释放掉匹配以及收集前面模板所分配的数据结构并返回不匹配
        undo_match();
        template_data_table = NULL;
    }

    return exec_status;
}


static void init_template_data_table(int dtsize)
{   
    int memsize = sizeof(struct template_data) * dtsize; 

    template_data_table = malloc(memsize);
    check_null(__FILE__, __func__, "template_data_table", template_data_table);

    memset(template_data_table, 0, memsize);
}


static void undo_match(void)
{
    free(template_data_table);
    template_data_table = NULL;
}


static match_function find_match_function
(
   char* template_name,
   struct match_info* mip 
)
{
    int i;
    int match_funcs_num = mip->match_funcs_num;
    struct template_match* match_funcs_table = mip->match_funcs_table;
    for (i=0; i<match_funcs_num; i++){ 
        if (is_equal(match_funcs_table[i].name, template_name)){
            return match_funcs_table[i].match_func;
        }
    }

    // 否则没有给定的模板,返回NULL
    return (match_function)0;
}


int check_match(int status, int op_idx, int template_id, void* template_data)
{
    // 返回不匹配
    if (! status) return UNMATCH;

    // 否则将收集到的数据存放到template_data_table中供后面使用
    template_data_table[op_idx].para_struct = template_data;
    template_data_table[op_idx].template_id = template_id;
    
    // 返回匹配
    return MATCH;
}


// 获取设备的数据模板信息表
void* get_template_data_table(void)
{
    return (void*)template_data_table;
}


const char* get_op_context()
{   
    // 为了调试方便加入的
    return op_context;
}


int has_operation_complemented(struct template_data* private_data, int op_idx)
{
   if (! check_null(__FILE__, __func__, "private_data", private_data)){
      printf("Detail: may be no corresponding driver being loaded\n");
      return 0;
   }

   void* para_struct = private_data[op_idx].para_struct;
   
   return (para_struct == NULL) ? 0 : 1;
}


// 通过相应的设备驱动匹配模块提供的最小功能集结构体
// 判断用户的配置信息是否满足
static int has_all_required_operations_complemented (struct match_info* mip)
{
    unsigned int record = *(mip->complementation_record);
    struct min_function_set* mfsp = mip->mfsp;
    *(mip->complementation_record) = 0; 

    if (record != mfsp->required_ops){
        int i;
        for (i=0; i<mfsp->required_ops_num; i++){
           int index = mfsp->required_ops_index[i];

           // record与required_ops不相等不等于就不匹配，只有规定的操作实现了
           // 就是匹配的
           if (! (record & (1<<index))){
              char msg[64];
              sprintf(msg, "'%s' is required", mfsp->required_ops_name[index]);
              report_error(__FILE__, __func__, msg); 

              return UNMATCH;
           }
        }
    }

    return MATCH;
}
