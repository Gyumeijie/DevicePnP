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
   struct command_sequence* cmd_seqp
)
{
    // TODO 对模板数据进行类型检查
    
    void* para_list; 
    para_list = find_para_list(template_data_owner_name, template_data_name);

    if (para_list == NULL)  return UNMATCH;

    int num_para = get_para_list_length(para_list);
    if (num_para == -1)  return UNMATCH;

    void* first_para = get_first_para(para_list);
 
    return do_fill_cmd_seq(first_para, num_para, &cmd_seqp);
}


static int do_fill_cmd_seq
(
    void* first_para,
    int num_para, 
    struct command_sequence** cmd_seq2p
)
{
    // 分配存储空间，如果分配失败则返回错误
    int bytes_size =  get_cmd_seq_size(num_para, first_para);
    if (! alloc_cmd_seq(bytes_size, cmd_seq2p)) return FAILURE;

    struct command_description* cmd_seq_desc = (*cmd_seq2p)->cmd_seq_desc;
    unsigned char* bytes_value = (*cmd_seq2p)->bytes_value;

    int i;
    mxml_node_t* para = first_para;
    for (i=0; i<bytes_size; ){
       const char* occupied_by = get_element_data(para, "occupied_by");
       strcpy(cmd_seq_desc[i].occupied_by, occupied_by);
       
       if (is_equal(occupied_by, "constant")){ 
           const char* byte_str = get_element_data(para, "text_value");
           if (byte_str == NULL) return FAILURE;
           
           bytes_value[i] = strtoul(byte_str, NULL, 16);
           
           i = i + 1;
       }else if(is_equal(occupied_by, "computed")){
           const char* size_str = get_element_data(para, "size");
           if (size_str == NULL) return FAILURE;
           int size = strtoul(size_str, NULL, 10);
           cmd_seq_desc[i].extra_cmd_desc.size = size;
           
           const char* compute_id_str = get_element_data(para, "compute_id");
           if (compute_id_str == NULL) return FAILURE;
           int compute_id = strtoul(compute_id_str, NULL, 10);
           cmd_seq_desc[i].extra_cmd_desc.compute_id = compute_id;
          
           i = i + size; 
       }else if(is_equal(occupied_by, "checksum")){

           i = i + 1;
       }else{
           // 未知的填充方式 
           return FAILURE;
       }
       
       para = get_next_sibling(para);
    }

    return SUCCESS;
}


static int get_cmd_seq_size(int len, void* para)
{
    int i;
    int bytes_size = 0;
    const char* occupied_by;
    for (i=0; i<len; i++){ 
       occupied_by = get_element_data(para, "occupied_by");
       if (is_equal(occupied_by, "constant") ||
           is_equal(occupied_by, "checksum")){
           bytes_size++;
       }else{
           const char* size_str = get_element_data(para, "size");
           if (size_str == NULL) return -1;
           int size = strtoul(size_str, NULL, 10);
           bytes_size += size; 
       }

       //TODO 当para_list的length大于实际的para项的话会报错，应当对此进行检测

       para = get_next_sibling(para);
    }

   return bytes_size; 
}


static int alloc_cmd_seq(int bytes_size, struct command_sequence** cmd_seq2p)
{
    (*cmd_seq2p)->bytes_size = bytes_size;

    char* bytes_value = malloc(sizeof(char)*bytes_size);  
    if (! check_null(__FILE__, __func__, "bytes_value", bytes_value)){
       return FAILURE;
    }
    (*cmd_seq2p)->bytes_value = bytes_value;

    struct command_description* cmd_seq_desc;
    cmd_seq_desc = malloc(sizeof(struct command_description)*bytes_size);
    if (! check_null(__FILE__, __func__, "cmd_seq_desc", cmd_seq_desc)){
       return FAILURE;
    }
    (*cmd_seq2p)->cmd_seq_desc = cmd_seq_desc;
    (*cmd_seq2p)->compute_funcs = malloc(sizeof(struct group_code_blocks));

    return SUCCESS;
}
