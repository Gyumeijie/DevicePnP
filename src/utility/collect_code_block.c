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
   void** code_block_struct
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
   void** code_block_struct
)
{
   void* group_blocks = find_element_in_context(template_data_context,
                                                "code_block_list",
                                                "name",
                                                code_block_name);

   // 对于一个具体的数据模板类型代码块不是必须存在的，但是如果配置文件
   // 中指定了有效的id，那么代码块就必须存在了，对于group_code在调用
   // collect_code_block的前会判断是否需要进行代码块的收集，所以这里如果
   // 找不到相应的代码块的话就要报错，而不是简单的返回一个FAILURE
   assure_not_null(__FILE__, __func__, "group_blocks", group_blocks);

   struct group_code_blocks* gcb = malloc(sizeof(struct group_code_blocks));
   *code_block_struct = gcb;

   int num_code_block = get_code_block_list_length(group_blocks);
   init_group_code_blocks(num_code_block, gcb);
   
   
   void* code_block = get_first_child(group_blocks);
   assure_not_null(__FILE__, __func__, "code_block", code_block);

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
   check_malloc(code_blocks);

   int** compiled_byte_code = malloc(sizeof((void*)0)*num_code_block);
   check_malloc(compiled_byte_code);

   memset(code_blocks, 0, sizeof((void*)0)*num_code_block);
   memset(compiled_byte_code, 0, sizeof((void*)0)*num_code_block);

   gcb->code_block_src_array = code_blocks;
   gcb->num_block = num_code_block;
   gcb->compiled_byte_code_array = compiled_byte_code;
}


static int get_code_block_list_length(void* code_block_list)
{
   const char* length_str = get_element_data(code_block_list, "length");
   check_element_data_existence("length", length_str);

   return strtoul(length_str, NULL, 10); 
}


static int do_single_code_block_collection
(
   void* template_data_context,
   const char* code_block_name,
   void** code_block_struct
)
{ 
   void* single_block = find_element_in_context(template_data_context,
                                                "code_block",
                                                "name",
                                                code_block_name);

   // 代码块是可选的，与group_block不同的是，如果在配置文件中找不到
   // 的话就直接返回
   if (single_block == NULL) return FAILURE;

   struct single_code_block* scb = malloc(sizeof(struct single_code_block)); 
   *code_block_struct = scb;

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
    const char* text_value_str = get_element_data(code_block, "text_value");
    check_element_data_existence("text_value", text_value_str);

    const char* id_str = get_element_data(code_block, "id");
    check_element_data_existence("id", id_str);
    unsigned int id = strtoul(id_str, NULL, 10);
    
    // 一个组的代码块相当于声明一个数组，每个代码块的id对应数组的
    // 下标而且id不应该重复
    if (id < num_code_block && code_block_src_array[id] == NULL){
        code_block_src_array[id] = text_value_str; 
    }else{
        char invalid_config_info[128];

        if (id >= num_code_block){
           sprintf(invalid_config_info, 
                   "bad code block id %d: id excess the length", 
                   id);
        }else{
           sprintf(invalid_config_info, 
                   "bad code block id %d: duplicate id",
                   id);
        }

        report_invalid_config_info_error("In code_block",
                                         invalid_config_info);    
    }
}


extern void check_code_block_ids_validity
(
   const struct code_block_ids_designated* ids_record,
   int num_code_block
)
{
   unsigned int len = ids_record->len;
   int* id_array = ids_record->id_array;

   int i; 
   for (i=0; i<len; i++){
      int code_block_id = id_array[i]; 
      if (code_block_id < NO_NEED_CODE_BLOCK || 
          code_block_id >= num_code_block)
      {
         char invalid_config_info[64];

         sprintf(invalid_config_info,
                 "invalid designated code block xxx_id %d",
                 code_block_id);

         report_invalid_config_info_error("In para", 
                                          invalid_config_info);    
      }
   }
}
