#include "load_xml.h"
#include "config_info_collect.h"
#include "driver_match.h"
#include "miscellaneous.h"
#include "command_sequence_fill.h" 
#include "interpreter.h"
#include "type_converter.h"
#include <stdio.h>

void fill_cmd_seq_dynamically
(  
   struct parameter_package* para_pkgp,
   struct command_sequence* cmd_seqp
)
{
    //TODO 处理参数包的个数与放置的参数个数不一样时的情况
    //(para_pkgp->num_para != para_pkgp->put_pos)

   struct group_code_blocks* compute_funcs = cmd_seqp->compute_funcs;

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
         process_parameter(para, compute_funcs, compute_id, &bytes_value[i], size);

         i = i + size;
      }else{
         calculate_checksum(bytes_value, i);
         i = i + 1;
      }
  }

   // 重置parameter_package中的fetch_tracer使得下一次可以重新使用
   reuse_parameter_package(para_pkgp);
}


static void process_parameter
(
   struct parameter* para,
   struct group_code_blocks* compute_funcs,
   int compute_id,
   char* start_addr_to_fill,
   int size
)
{
   unsigned int result;

   if (compute_id > NO_NEED_COMPUTATION){
       // 如果compute_id是有效的，那么就需要实际的计算过程
       result = do_computation(compute_id, compute_funcs, para);
   }else {
       // 如果compute_id为是NO_NEED_COMPUTATION的话，即不需要计算
       // 那么默认的是该参数可以直接或者通过转型成32为无符号整型数
       result = cast_to_uint32(para);
   }

   split_uint32_into_bytes(start_addr_to_fill, size, result);
}


static unsigned int cast_to_uint32(struct parameter* para)
{
   char* para_type = para->para_type;
   int value = para->value;
   unsigned int result;

   // 如果存储的是变量的指针，那么就将value值转型成不同类型的指针
   // 取出相应的值
   // 这里按照可能的常见变量类型安排类型判断的顺序
   if (para->is_pointer){
       if (is_equal(para_type, "int")){
          result =  *(int*)value;
       }else if (is_equal(para_type, "float")){
          result = *(float*)value;
       }else if (is_equal(para_type, "char")){
          result = *(char*)value;
       }else{
          //TODO
       }
   
   }else{
      // 如果para->value不是指针的话，就直接转型成32为无符号整型数
      result = (unsigned int)para->value;
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


// 注意到最后切分成字节的数据的类型一定是无符号整型数
// 但是在转化成无符号整型数之前数据的类型可能是浮点数
// 或其它类型的，而且可能需要进行一些计算；这个函数就
// 执行的是最后的共同步骤即将32为无符号整数，按照size
// 给定的字节数进行切分，并将切分的字节存放在最后要发
// 送的bytes_value数组的相应位置
static void split_uint32_into_bytes
(
   char* bytes_value, 
   int size, 
   unsigned int para
)
{
    unsigned int temp = para;

    int i;
    for (i=0; i<size; i++){
      bytes_value[i] = temp & 0x000000FF;
      temp >>= 8; 
    }
}


// 1. compute_id是局部的，不同驱动函数使用compute_id是独立的，
//    compute_id是针对一个具体的参数而言的，是在xml中用于区分
//    不同的代码块的标识，在一个驱动函数中如果相同性质的代码块
//    有多个的话，那么这些代码块的源码就会收集到一个数组中，这时
//    id号就是数组的下标
// 2. 参数的不同计算流程用解析器来执行，这里只需要根据compute_id
//    从驱动函数的模板数据中提取代码块的首地址，然后调用解析器的
//    run_code函数即可
// 3. 这里需要注入的依赖有两个：需要计算的参数和计算后的结果
//    因为依赖可以很方便注入进去，但是计算后的结果怎么返回是个问题
//    这里采用将结果(result)也作为一个依赖注入进去，需要返回的结果
//    就通过赋值的形式个result
// 4. 注入的依赖如果地址不会变的话就可以避免重新编译了，因为参数包
//    是从堆上分配，如果不显式释放的话注入的依赖信息是不会丢失的
static int do_computation
(
   int compute_id,
   struct group_code_blocks* compute_funcs,
   struct parameter* para
)
{
    static int  result;

    int* code =  compute_funcs->compiled_byte_code_array[compute_id]; 
    if (code != NULL){
       printf("value is %f\n", *(float*)para->value);
       printf("type is %s\n", para->para_type);
       run_code(code);
    }else{ 
       // 加入该代码块依赖与主程序的变量
       struct dependency_items* dep_items;
       dep_items = init_dependency_items(2);
       int num_type = strtype_to_numtype(para->para_type, para->is_pointer);

       add_dependency_item(dep_items, "para",  (void*)&para->value, num_type);
       add_dependency_item(dep_items, "result", (void*)&result, INT);

        // 根据compute_id获取源码数据
        const char* src = compute_funcs->code_block_src_array[compute_id];

        // 将编译的代码放在存放在相应的字段中
        code = compile_src_code(dep_items, src);
        compute_funcs->compiled_byte_code_array[compute_id] = code;
        run_code(code);
    }

    printf("result is %d\n", result);
    return result;
}


