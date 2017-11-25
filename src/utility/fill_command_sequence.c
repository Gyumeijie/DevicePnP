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
   char* global_or_op_name,
   char* para_name,
   struct command_sequence* cmd_seqp
)
{
    int num_para;
    mxml_node_t  *first_para;

    if (! get_first_para_and_num_para(global_or_op_name, 
                                      para_name,
                                      &num_para,
                                      &first_para)){
       return UNMATCH;
    }
   
    return do_fill_cmd_seq(first_para, num_para, &cmd_seqp);
}


static int do_fill_cmd_seq
(
    mxml_node_t* first_para,
    int num_para, 
    struct command_sequence** cmd_seq2p
)
{
    //分配存储空间，如果分配失败则返回错误
    int bytes_size =  get_cmd_seq_size(num_para, first_para);
    if (! alloc_cmd_seq(bytes_size, cmd_seq2p)) return FAILURE;

    struct command_description* cmd_seq_desc = (*cmd_seq2p)->cmd_seq_desc;
    unsigned char* bytes_value = (*cmd_seq2p)->bytes_value;

    int i;
    mxml_node_t* para = first_para;
    for (i=0; i<bytes_size; ){
       const char* occupied_by = mxmlElementGetAttr(para, "occupied_by");
       strcpy(cmd_seq_desc[i].occupied_by, occupied_by);
       
       if (is_equal(occupied_by, "constant")){ 
           bytes_value[i] = strtol(mxmlGetText(para, NULL), NULL, 16);
           i = i + 1;
       }else if(is_equal(occupied_by, "computed")){
           int size = strtoul(mxmlElementGetAttr(para, "size"), NULL, 10);
           cmd_seq_desc[i].extra_cmd_desc.size = size;
           
           int compute_id = strtoul(mxmlElementGetAttr(para, "compute_id"),
                                    NULL, 
                                    10);
           cmd_seq_desc[i].extra_cmd_desc.compute_id = compute_id;
          
           i = i + size; 
       }else{
           i = i + 1;
       }
       
       //para = skip_text_node(para, "occupied_by");
       para = skip_text_node(mxmlGetNextSibling(para), "occupied_by");
    }

    return SUCCESS;
}


static int get_cmd_seq_size(int len, mxml_node_t* para)
{
    int bytes_size = 0;
    const char* occupied_by;

    int i;
    for (i=0; i<len; i++){ 
       occupied_by  = mxmlElementGetAttr(para, "occupied_by");
       if (is_equal(occupied_by, "constant") ||
           is_equal(occupied_by, "checksum")){
           bytes_size++;
       }else{
           int size = strtoul(mxmlElementGetAttr(para, "size"), NULL, 10);
           bytes_size += size; 
       }

       //TODO 当para_list的length大于实际的para项的话会报错，应当对此进行检测
       //TODO 尽量屏蔽细节，用更通用的函数接口去代替
       //para = skip_text_node(para, "occupied_by");
       //修改了skip_text_node的逻辑, 后面有时间换成get_next_sibling
       para = skip_text_node(mxmlGetNextSibling(para), "occupied_by");
    }

   return bytes_size; 
}


static int alloc_cmd_seq(int bytes_size, struct command_sequence** cmd_seq2p)
{

    (*cmd_seq2p)->bytes_size = bytes_size;

    char* bytes_value = malloc(sizeof(char)*bytes_size);  
    //TODO 为check_null换一个更好的名字
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
