#include "config_info_collect.h"
#include "collect_code_block.h"
#include "error_report.h"
#include <stdlib.h>

/**
 *  1. 该模块从功能是xml搜集代码块，任何模板或者驱动函数都可以有
 *     相应的代码块，因此收集过程不应该涉及到具体模板或者驱动函数
 *     的模板数据结构
 *  2. 对于一个驱动函数而言，相同性质的代码块可能只有一个，例如preconditon
 *     函数，也可以有多个例如compute函数或者postprocess函数，为了是收集
 *     函数更通用，应该屏蔽这些细节；具体地使用一个变量来指定代码块的模式
 *     是单独存在的还是一个组的，如果是一个组的则每个代码块必须有id号且作为
 *     在这个组的唯一标识
 *  3. 如果相同性质的代码块是一个组的形式存在的，比如有多个代码块都是作为
 *     compute函数存在的，这些代码块都是包含在<code_block>标签中,而这些标签
 *     由包含在<code_block_list>标签中，该标签中有一个length属性用来表示这个
 *     组的代码块的个数以及name属性表示这些代码块的共同的用途，例如compute
 *  4. 这里的SINGLE和GROUP代码组织方式是指从逻辑上来讲对于一个驱动函数而言
 *     代码块可能有的个数，如果只能有一个那么就是SINGLE方式，否则就是GROUP
 */


int collect_code_block
(
   const char* op_name,
   const char* template_data_name,
   const char* code_block_name,
   int code_block_mode,
   void* code_block_struct
)
{
   // code_block的name属性在template_data的"作用域"下应该是唯一的
   // 如果一个操作模板有多个template_data的话，而且都有code_block
   // 的时候，其name属性可能会出现冲突；为此将code_block的name属性
   // 放在template_data的上下文下进行搜索
   void* op_context = find_device_operation(op_name);
   void* template_data_context = find_element_in_context(op_context,
                                                         "template_data",
                                                         "name",
                                                         template_data_name);

   if (code_block_mode == SINGLE){
       return do_single_code_block_collection(template_data_context,
                                              code_block_name,
                                              code_block_struct);
   }else{
       return do_group_code_blocks_collection(template_data_context,
                                              code_block_name,
                                              code_block_struct);
   }
}


static int do_group_code_blocks_collection
(
   void* template_data_context,
   const char* code_block_name,
   struct group_code_blocks* gcb
)
{
   void* group_blocks = find_element_in_context(template_data_context,
                                                "code_block_list",
                                                "name",
                                                code_block_name);

   if (group_blocks == NULL) return FAILURE;

   int num_code_block = get_code_block_list_length(group_blocks);
   init_group_code_blocks(num_code_block, gcb);
   
   void* code_block = get_first_child(group_blocks);
   if (code_block == NULL) return FAILURE;

   int i;
   const char** code_block_src_array = gcb->code_block_src_array;
   for (i=0; i<num_code_block; i++){
       install_code_block(code_block, code_block_src_array, num_code_block);
       code_block = get_next_sibling(code_block);
   }

   return SUCCESS;
}


static void init_group_code_blocks
(
   int num_code_block,
   struct group_code_blocks* gcb
)
{
   const char** code_blocks = malloc(sizeof((void*)0)*num_code_block);
   int** compiled_byte_code = malloc(sizeof((void*)0)*num_code_block);

   memset(code_blocks, 0, sizeof((void*)0)*num_code_block);
   memset(compiled_byte_code, 0, sizeof((void*)0)*num_code_block);

   gcb->code_block_src_array = code_blocks;
   gcb->num_block = num_code_block;
   gcb->compiled_byte_code_array = compiled_byte_code;
}


static int get_code_block_list_length(void* code_block_list)
{
   // TODO 注意如果配置文件中没有length属性，将会报错这种是比较常见的模式
   // 应该有一个专门的报错函数，整理一下error_report
   const char* length_str = get_element_data(code_block_list, "length");
   if (length_str == NULL) return -1;

   return strtoul(length_str, NULL, 10); 
}


static int do_single_code_block_collection
(
   void* template_data_context,
   const char* code_block_name,
   struct single_code_block* scb
)
{ 
   void* single_block = find_element_in_context(template_data_context,
                                                "code_block",
                                                "name",
                                                code_block_name);

   if (single_block == NULL) return FAILURE;

   scb->code_block_src = (void*)get_element_data(single_block, "text_value");
   scb->compiled_byte_code = NULL;

   return SUCCESS;
}


static void install_code_block
(
   void* code_block,
   const char** code_block_src_array,
   const int num_code_block
)
{
    const char* src_code = get_element_data(code_block, "text_value");
    unsigned int id =  strtoul(get_element_data(code_block, "id"), NULL, 10);
    
    // 一个组的代码块相当于声明一个数组，每个代码块的id对应数组的
    // 下标而且id不应该重复
    if (id < num_code_block && code_block_src_array[id] == NULL){
        code_block_src_array[id] = src_code; 
    }else{
        printf("Bad code block id %d: ", id);

        if (id >= num_code_block){
           printf("id excess the length\n");
        }else{
           printf("dulplicate id\n");
        }

        exit(-1);
    }
}
