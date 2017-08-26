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
int do_match(void* (*init_template_data_table)(void),
             int (*find_and_exec_match_func)(char* func_name),
             void (*undo_match)(void)
             )
{
    int length;
    char* op_name = NULL;
    int template_id;
    char template_name[MAX_TEMPLATE_NAME_LENGTH];
    int exec_status;
    

    //初始化设备的模板参数结构体表
    template_data_table = (struct template_data*)init_template_data_table();

    //先通过全局变量匹配函数来匹配以及收集全局的参数信息
#if 0
    exec_status  = find_and_exec_match_func("global");
    if (exec_status == 0){
        undo_match();
        return 0;
    }
#endif 
    //然后依次匹配以及收集每个模板的参数
    int i;
    length = get_op_list_length();
    for (i=0; i<length; i++){
        op_name = get_op_name();
        template_id = get_op_template_id(op_name);
        
        //构造模板名 设备类型_操作名_templatexxx，其中xxx为template_id
        sprintf(template_name, "%s_template%d", op_name, template_id);
        
        //通过模板名找到给定模板的匹配函数入口地址并执行
        exec_status = find_and_exec_match_func(template_name);

        if (exec_status == 0){
           //释放掉匹配以及收集前面模板所分配的数据结构并返回不匹配
           undo_match();
           template_data_table = NULL;
           return 0;
        }
    }

    //返回匹配
    return 1;
}

void* get_template_data_table(void)
{
    return (void*)template_data_table;
}

