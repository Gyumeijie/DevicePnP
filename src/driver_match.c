#include "driver_match.h"
#include "config_info_collect.h"
#include "error_report.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>

static const char* op_context = NULL;

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
   
    if(!check_null(__FILE__, __func__, "mip", mip)) return UNMATCH;
    g_mip = mip;
    
    //初始化设备的模板参数结构体表
    init_template_data_table(mip->data_table_size);

    //先通过全局变量匹配函数来匹配以及收集全局的参数信息
    op_context = "global";
    if (has_global_config_item() && !try_match("global")) return UNMATCH;

    //然后根据配置文件依次匹配以及收集每个模板的参数
    int i;
    length = get_op_list_length();
    for (i=0; i<length; i++){
        op_name = get_op_name();
        template_id = get_op_template_id(op_name);
        op_context = op_name;
             
        construct_template_name(template_name, op_name, template_id);
        
        if (!try_match(template_name)) return UNMATCH;
    }

    
    //检查通用设备驱动是否定义了最小功能集，如果有则检查配置文件的配置信息是否
    //涵盖了这个最小功能集
    op_context = NULL;
    if (mip->mfsp != NULL){
       return has_all_required_ops_complemented();
   }

    //返回匹配
    return MATCH;
}


static void construct_template_name(char* template_name, char* op_name,
                                    int template_id)
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
        template_data_table = NULL;
    }

    return exec_status;
}


static void init_template_data_table(int dtsize)
{   
    int memsize = sizeof(struct template_data)*dtsize; 

    template_data_table = malloc(memsize);
    check_null(__FILE__, __func__, "template_data_table", template_data_table);

    memset(template_data_table, 0, memsize);
}


static void undo_match(void)
{
    free(template_data_table);
    template_data_table = NULL;
}


//TODO 检查name是否为空
static int find_and_exec_match_func(char* name)
{
    //查找匹配函数，如果没有找到则返回不匹配，并给出具体的原因
    match_func_ptr match_func = find_match_func(name);
    if (!check_null(__FILE__, __func__, "match_func", match_func)){
        printf("Detail: can't not find matching function of template '%s'\n",
                                                                      name);
        return UNMATCH;
    }

    //执行函数并返回匹配函数的结果
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
  
    match_funcs_num = g_mip->match_funcs_num;
    match_funcs_table = g_mip->match_funcs_table;
    for (i=0; i<match_funcs_num; i++){ 
        //TODO match_funcs_table[i].name 可能为NULL
        if (strcmp(match_funcs_table[i].name, name) == 0){
            return match_funcs_table[i].match_func;
        }
    }

    //否则没有给定的模板,返回NULL
    return NULL;
}


int check_match(int status, int op_idx, int template_id, void* template_data)
{
    //返回不匹配
    if (!status) return UNMATCH;

    //否则将收集到的数据存放到template_data_table中供后面使用
    template_data_table[op_idx].para_struct = template_data;
    template_data_table[op_idx].template_id = template_id;
    //TODO 添加para_struct_type
    
    //返回匹配
    return MATCH;
}


/**
 *　输入：无
 *　输出：无
 *　功能：返回设备的对通用设备驱动的配置信息，该函数在判断匹配后有设备驱动绑定
 *　      模块调用，将此信息赋值给设备结构体中的相应字段
 */
void* get_template_data_table(void)
{
    return (void*)template_data_table;
}


const char* get_op_context()
{   
    //为了调试方便加入的
    return op_context;
}

/**
 *　输入：具体设备的驱动模板配置信息结构体指针private_data，以及一个用于判断给
 *        定操作是否配置实现的操作索引号op_idx
 *　输出：返回一个整数表示条件是否满足　
 *　功能：
 */
int has_op_complemented(struct template_data* private_data, int op_idx)
{
   if (!check_null(__FILE__, __func__, "private_data", private_data)){
      printf("Detail: may be no corresponding driver being loaded\n");
      return 0;
   }

   void* para_struct  = private_data[op_idx].para_struct;
   
   return (para_struct == NULL) ? 0 : 1;
}


/**
 *　输入：无
 *　输出：返回一个整数表示条件是否满足
 *  功能：通过相应的设备驱动匹配模块提供的最小功能集结构体
 *        判断用户的配置信息是否满足
 */
static int has_all_required_ops_complemented(void)
{
    unsigned int record = *(g_mip->complementation_record);
    struct min_function_set* mfsp = g_mip->mfsp;
    char msg[64];
    *(g_mip->complementation_record) = 0; 

    if (record != mfsp->required_ops ){
        int i, index;
        for (i=0; i< mfsp->required_ops_num; i++){
           index = mfsp->required_ops_index[i];

           //record与required_ops不相等不等于就不匹配，只有规定的操作实现了就是
           //匹配的
           if (!(record & (1<<index))){
              sprintf(msg, "'%s' is required", mfsp->required_ops_name[index]);
              report_error(__FILE__, __func__, msg); 
              return UNMATCH;
           }
        }
    }

    return MATCH;
}
