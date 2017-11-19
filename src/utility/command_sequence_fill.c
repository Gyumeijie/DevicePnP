#include "load_xml.h"
#include "config_info_collect.h"
#include "driver_match.h"
#include "miscellaneous.h"
#include "parameter_package.h"
#include "command_sequence_fill.h" 
#include <stdio.h>

void fill_cmd_seq_dynamically(struct command_sequence* cmd_seqp,
                              struct parameter_package* para_pkgp)
{
    //TODO 处理参数包的个数与放置的参数个数不一样时的情况
    //(para_pkgp->num_para != para_pkgp->put_pos)

    int bytes_size = cmd_seqp->bytes_size;
    char* bytes_value = cmd_seqp->bytes_value;
    struct command_description* cmd_seq_desc = cmd_seqp->cmd_seq_desc;

    int i = 0;
    while (i<bytes_size){
       if (is_equal(cmd_seq_desc[i].occupied_by, "constant")){
          i = i + 1;
       }else if(is_equal(cmd_seq_desc[i].occupied_by, "computed")){ 
          int size = cmd_seq_desc[i].extra_cmd_desc.size;
          int compute_id = cmd_seq_desc[i].extra_cmd_desc.compute_id;
          struct parameter* para = fetch_para(para_pkgp); 
          void* value = (void*)&para->value;
              
          dispatch_by_compute_id(compute_id, &bytes_value[i], size, value);

          i = i + size;
       }else{
          calculate_checksum(bytes_value, i);
          i = i + 1;
       }
   }
}


static void calculate_checksum(char* bytes_value, int size)
{
    unsigned char checksum = 0; 
    int i;
    for (i=0; i<size; i++){
       checksum += bytes_value[i]; 
    }

    bytes_value[size] = checksum;
}


static void compute_func0(char* bytes_value, int size, void* para)
{
    int temp = *(int*)para;

    int i;
    for (i=0; i<size; i++){
      bytes_value[i] = temp & 0x000000FF;
      temp >>= 8; 
    }
}


static compute_func compute_funcs[MAX_COMPUTE_FUNCTION_NUM] = {
   compute_func0,
};


static struct compute_functions_manager mgr = {
    SET_BITS(PRESET_COMPUTE_FUNCTION_NUM), 
    compute_funcs
};


int register_compute_func(int compute_id, compute_func func)
{
    //TODO 当超过最大的函数容量时报告错误
    if (is_bad_compute_id(compute_id)) return 1;

    //TODO 添加global_config, 用于配置程序的工作方式
    //例如可以覆盖或者不能覆盖已经注册的函数
    //这里选择是不能覆盖的
    if (has_func_registered(compute_id)) return 1;

    mgr.compute_funcs_arr[compute_id] = func;
    SET_BIT(compute_id, mgr.funcs_bitmap);

    return 0;
}


void unregister_compute_func(int compute_id)
{
    CLEAR_BIT(compute_id, mgr.funcs_bitmap);
}


static Boolean has_func_registered(int compute_id)
{
   return IS_BIT_SET(compute_id, mgr.funcs_bitmap); 
}


static Boolean is_bad_compute_id(int compute_id)
{
   return (compute_id < PRESET_COMPUTE_FUNCTION_NUM || 
           compute_id > (MAX_COMPUTE_FUNCTION_NUM -1));
}


static void dispatch_by_compute_id(int compute_id, char* bytes_value,
                                   int size, void* para)
{
    if (has_func_registered(compute_id)){
        compute_funcs[compute_id](bytes_value, size, para);
    }
    //TODO 报告错误，说明compute_id对应的函数没有实现
}



void use_compute_func(int func_id, char* bytes_value, int size, void* para)
{
   dispatch_by_compute_id(func_id, bytes_value, size, para);   
}


//为了方便使用者查看哪些槽位号可用来注册自定义的计算函数
void inspect_compute_funcs_bitmap(int column)
{
   int col = column;
   if (column > MAX_COMPUTE_FUNCTION_NUM || column <= 0){
       col = MAX_COMPUTE_FUNCTION_NUM;
   }
   int row;
   row = (MAX_COMPUTE_FUNCTION_NUM + (col - 1)) / col;
   int func_bitmap = mgr.funcs_bitmap;

   int i, j;    
   int remaining = MAX_COMPUTE_FUNCTION_NUM;
   for (i=0; i<row; i++){
      int start = i * col;
      int end = (col < remaining) ?
                ((i + 1) * col - 1) : (MAX_COMPUTE_FUNCTION_NUM -1);
      printf("[%02d-%02d]: ", start, end); 

      //最后一行可能不足col列，这里没有将最后一行单独拿出来进行处理，因此
      //需要计算每一行真实的列数
      int real_col_per_row = (col < remaining) ? col : remaining;
      remaining = remaining - real_col_per_row;
      for (j=0; j<real_col_per_row; j++){
        char trailing_ch = (j + 1) % (real_col_per_row) ? ' ' : '\n';
        printf("%d%c", IS_BIT_SET(i * col + j, func_bitmap), trailing_ch); 
      }
   }
}
