#include "config_info_collect.h"
#include "error_report.h"
#include "miscellaneous.h"
#include "fill_command_sequence.h"
#include "collect_code_block.h"
#include <string.h>
#include <malloc.h>
#include <stdio.h>


int fill_command_sequence
(
   const char* template_data_owner_name,
   const char* template_data_name,
   struct command_sequence* cmd_seqp,
   int* need_to_collect_code_block,
   struct code_block_ids_designated* compute_ids_record
)
{
   // 先检测模板数据的类型
   check_template_data_type(template_data_owner_name,
                            template_data_name,
                            "command_sequence");  

   void* first_para;
   int num_para;
   prepare_para(template_data_owner_name,
                template_data_name,
                &first_para,
                &num_para);
     
   return do_fill_cmd_seq(first_para,
                          num_para,
                          &cmd_seqp,
                          need_to_collect_code_block,
                          compute_ids_record);
}


static int do_fill_cmd_seq
(
   void* first_para,
   int num_para, 
   struct command_sequence** cmd_seq2p,
   int* need_to_collect_code_block,
   struct code_block_ids_designated* compute_ids_record
)
{
   int bytes_size = get_cmd_seq_size(num_para, first_para);
   alloc_cmd_seq(bytes_size, cmd_seq2p);

   // 由于事先不知道有多少个参数会指定compute_id，所以先分配num_para
   // 大小的空间
   compute_ids_record->id_array = malloc(sizeof(int)*num_para);   

   struct command_description* cmd_seq_desc = (*cmd_seq2p)->cmd_seq_desc;
   unsigned char* bytes_value = (*cmd_seq2p)->bytes_value;

   int i;
   const void* para = first_para;
   int num_para_need_computed = 0;
   int* id_array = compute_ids_record->id_array;
   for (i=0; i<bytes_size; ){

      const char* occupied_by_str = get_element_data(para, "occupied_by");
      check_element_data_existence("occupied_by", occupied_by_str);
      strcpy(cmd_seq_desc[i].occupied_by, occupied_by_str);
      
      // 下面根据填充方式(occupied_by)收集相应的信息
      
      if (is_equal(occupied_by_str, "constant")){ 

          const char* text_value_str = get_element_data(para, "text_value");
          check_element_data_existence("text_value", text_value_str);
          bytes_value[i] = strtoul(text_value_str, NULL, 16);
          
          i = i + 1;
      }else if(is_equal(occupied_by_str, "computed")){

          const char* size_str = get_element_data(para, "size");
          check_element_data_existence("size", size_str);
          int size = strtoul(size_str, NULL, 10);
          cmd_seq_desc[i].extra_cmd_desc.size = size;
          
          const char* compute_id_str = get_element_data(para, "compute_id");
          check_element_data_existence("compute_id", compute_id_str);
          int compute_id = strtoul(compute_id_str, NULL, 10);
          cmd_seq_desc[i].extra_cmd_desc.compute_id = compute_id;
         
          // 如果compute_id是有效的，那么就需要收集代码块，而且只需要设置一次
          if (!(*need_to_collect_code_block) && 
              (compute_id >= 0))
          {
             *need_to_collect_code_block = 1; 
          }

          // 记录compute_id
          id_array[num_para_need_computed] = compute_id; 
          num_para_need_computed++;

          i = i + size; 
      }else if(is_equal(occupied_by_str, "checksum")){

          i = i + 1;
      }else{

          // 未知的填充方式 
          return FAILURE;
      }
      
      para = get_next_sibling(para);
   }

   compute_ids_record->len = num_para_need_computed;
   
   return SUCCESS;
}


static int get_cmd_seq_size(int len, void* para)
{
   int i;
   int bytes_size = 0;
   for (i=0; i<len; i++){ 

      // 当para_list的length大于实际的para项时话也会因为找不到occupied_by
      // 属性而报错
      const char* occupied_by_str = get_element_data(para, "occupied_by");
      check_element_data_existence("occupied_by", occupied_by_str);

      if (is_equal(occupied_by_str, "constant") ||
          is_equal(occupied_by_str, "checksum"))
      {
          bytes_size++;
      }else {
          const char* size_str = get_element_data(para, "size");
          check_element_data_existence("size", size_str);
          int size = strtoul(size_str, NULL, 10);

          bytes_size += size; 
       }

      para = get_next_sibling(para);
   }

  return bytes_size; 
}


static void alloc_cmd_seq(int bytes_size, struct command_sequence** cmd_seq2p)
{
   (*cmd_seq2p)->bytes_size = bytes_size;

   char* bytes_value = malloc(sizeof(char)*bytes_size);  
   check_malloc(bytes_value);
   (*cmd_seq2p)->bytes_value = bytes_value;

   struct command_description* cmd_seq_desc;
   cmd_seq_desc = malloc(sizeof(struct command_description)*bytes_size);
   check_malloc(cmd_seq_desc);

   (*cmd_seq2p)->cmd_seq_desc = cmd_seq_desc;
   (*cmd_seq2p)->compute_funcs = NULL;
}
