#include "miscellaneous.h"
#include "parameter_package.h"
#include <string.h>
#include <malloc.h>

//TODO 调整参数的顺序以及更好的命名
static int fill_parameter_package
(
    struct parameter_package* para_pkgp,
    void* value,
    char* type, 
    int put_strategy,
    int put_pos, 
    Boolean is_stored_as_address
)
{
    //TODO 是否需要自动转换调用，还是给出一个错误/警告
    if (para_pkgp->put_strategy != put_strategy) return 1;
    if (can_not_put(para_pkgp, put_pos, put_strategy)) return 1;

    struct parameter* paras = para_pkgp->paras;
    int put_tracer = para_pkgp->put_tracer;
    paras[put_tracer].para_type = type; 
    paras[put_tracer].is_pointer = is_stored_as_address; 

    //如果存入的是变量的地址的话，那么就以int类型存储该地址的值
    char* src_type = is_stored_as_address ? "int" : type;
    store_data(&paras[put_tracer].value, value, src_type, src_type); 
    
    update_put_tracer(para_pkgp, put_strategy, put_pos);

    return 0;
}


//下面一组put方法放置参数的方法适合集中准备参数的情况，并且放置的顺序需要
//用户负责
int put_value
(
    struct parameter_package* para_pkgp,
    void* value, 
    char* type
)
{   
    //变量的值(等价于传递值，接受这个参数的函数只能读取这个值)
    return fill_parameter_package(para_pkgp,
                                  value,
                                  type,
                                  PUT_WITHOUT_POS,
                                  MEANINGLESS_PUT_POS,
                                  False);
}


int put_literal
(
   struct parameter_package* para_pkgp,
   void* value, 
   char* type
)
{
    //字面量(等价于传递值)
    void* literal_keeper = convert_type(value, type);
    return fill_parameter_package(para_pkgp,
                                  literal_keeper, 
                                  type, 
                                  PUT_WITHOUT_POS,
                                  MEANINGLESS_PUT_POS,
                                  False);
}


int put_address
(
   struct parameter_package* para_pkgp,
   void* var_addr, 
   char* type
)
{
    //变量地址（等价于传递指针, 接受这个参数的函数可以通过指针修改变量的值）
    int var_addr_keeper = (int)var_addr;
    return fill_parameter_package(para_pkgp,
                                  &var_addr_keeper, type, 
                                  PUT_WITHOUT_POS,
                                  MEANINGLESS_PUT_POS,
                                  True);
}


//下面一组put方法放置参数的位置可有用户显示指定，同一个参数包的参数放置的顺序
//更灵活
int put_value_with_pos
(
   int put_pos, 
   struct parameter_package* para_pkgp, 
   void* value,
   char* type
)
{
   return fill_parameter_package(para_pkgp, 
                                 value,
                                 type,
                                 PUT_WITHOUT_POS,
                                 put_pos, False);
}


int put_literal_with_pos
(
   int put_pos, 
   struct parameter_package* para_pkgp,
   void* value, 
   char* type
)
{
    void* literal_keeper = convert_type(value, type);
    return fill_parameter_package(para_pkgp,
                                  literal_keeper,
                                  type,
                                  PUT_WITH_POS,
                                  put_pos,
                                  False);
}


int put_address_with_pos
( 
   int put_pos, 
   struct parameter_package* para_pkgp, 
   void* var_addr,
   char* type
)
{
    int var_addr_keeper = (int)var_addr;
    return fill_parameter_package(para_pkgp,
                                  &var_addr_keeper,
                                  type, 
                                  PUT_WITHOUT_POS,
                                  put_pos,
                                  True);
}


Boolean is_all_parameter_set(struct parameter_package* para_pkgp)
{
    int put_tracer = para_pkgp->put_tracer;
    int num_para = para_pkgp->num_para;

    // 不使用位置参数
    if (para_pkgp->put_strategy == PUT_WITHOUT_POS){
        return put_tracer == num_para;
    }else{
    // 使用位置存放参数, put_tracer的每一位代表着一个参数
        return (put_tracer & num_para) == num_para;
    }
}


static void update_put_tracer
(
   struct parameter_package* para_pkgp, 
   int put_strategy,
   int put_pos
)
{
    // 放置策略不同跟踪put的方法也不一样
    if (put_strategy == PUT_WITHOUT_POS){
         para_pkgp->put_tracer++;
    }else{
         SET_BIT(put_pos, para_pkgp->put_tracer);
    }
}


static Boolean can_not_put
(
   struct parameter_package* para_pkgp, 
   int put_pos, 
   int put_strategy
)
{
    if (is_all_parameter_set(para_pkgp)) return True;

    // 在使用位置信息放置参数时，如果某个位置已经放置了则不能再放了
    if (put_strategy == PUT_WITH_POS){
        int put_tracer = para_pkgp->put_tracer;
        return !IS_BIT_SET(put_pos, put_tracer);
     }

    return False;
}


struct parameter* fetch_para(struct parameter_package* para_pkgp)
{
    struct parameter* parap = &para_pkgp->paras[para_pkgp->fetch_tracer];
    para_pkgp->fetch_tracer++;

    return parap;
}


void store_data
(
    void* dest, 
    void* src, 
    const char* dest_type,
    const char* src_type
)
{
    if (is_inttype(dest_type)){
       int len = parse_inttype_for_length(dest_type);
       (len == 32) ? store_int32type_data_from(src_type, dest, src)
                   : store_int16type_data_from(src_type, dest, src);
    }else if (is_equal(dest_type, "float")){
       store_floattype_data_from(src_type, dest, src);
    }else if (is_equal(dest_type, "char")){
       store_chartype_data_from(src_type, dest, src);
    }else{
       // 不执行实际操作，这里忽略
    }
}


static void store_floattype_data_from
(
    const char* src_type, 
    void* dest,
    void* src
)
{   
    if (is_equal(src_type, "float")){
       TO_FLOAT(dest) = TO_FLOAT(src);
    }else if (is_inttype(src_type)){
       int len = parse_inttype_for_length(src_type);
       TO_FLOAT(dest) = (len == 32) ? TO_INT(src) : TO_SHORT_INT(src);
    }else{
       // 由char转float不常见，这里先不写以后有需求的话在写
    }
}


static void store_chartype_data_from
(
    const char* src_type, 
    void* dest,
    void* src
)
{
    if (is_equal(src_type, "char")){
       TO_CHAR(dest) = TO_CHAR(src);
    }else if (is_inttype(src_type)){
       int len = parse_inttype_for_length(src_type);
       TO_CHAR(dest) = (len == 32) ? TO_INT(src) : TO_SHORT_INT(src);
    }else{
       // 由char转float不常见，这里先不写以后有需求的话在写
    }
}


static void store_int16type_data_from
(
    const char* src_type, 
    void* dest,
    void* src
)
{
    if (is_inttype(src_type)){
       int len = parse_inttype_for_length(src_type);
       TO_SHORT_INT(dest) = (len == 32) ? TO_INT(src) : TO_SHORT_INT(src);
    }else if (is_equal(src_type, "float")){
       TO_SHORT_INT(dest) = TO_FLOAT(src);
    }else{
       TO_SHORT_INT(dest) = TO_CHAR(src);
    }
}


static void store_int32type_data_from
(
    const char* src_type, 
    void* dest,
    void* src
)
{
    if (is_inttype(src_type)){
       int len = parse_inttype_for_length(src_type);
       TO_INT(dest) = (len == 32) ? TO_INT(src) : TO_SHORT_INT(src);
    }else if (is_equal(src_type, "float")){
       TO_INT(dest) = TO_FLOAT(src);
    }else{
       TO_INT(dest) = TO_CHAR(src);
    }

}


struct parameter_package* init_parameter_package
(
    int num_para, 
    int put_strategy
)
{
    struct parameter_package* para_pkgp;
    para_pkgp = malloc(sizeof(struct parameter_package));
    para_pkgp->num_para = num_para;
    para_pkgp->put_strategy = put_strategy;
    para_pkgp->put_tracer = para_pkgp->fetch_tracer = 0; 
    para_pkgp->paras = malloc(sizeof(struct parameter) * num_para);

    return para_pkgp;
}


void destroy_parameter_package(struct parameter_package* para_pkgp)
{
    free(para_pkgp->paras);
    free(para_pkgp);
}


// 这里不释放paras是为了可以重用该堆空间，避免频繁分配/释放堆空间影响效率
void reset_parameter_package(struct parameter_package* para_pkgp)
{ 
    para_pkgp->put_tracer = para_pkgp->fetch_tracer = 0; 
}


// 因为在fetch_para的时候更新了fetch_tracer，如果想重新使用参数包中的参数
// 信息的时候需要重新设置fetch_tracer
void reuse_parameter_package(struct parameter_package* para_pkgp)
{
    para_pkgp->fetch_tracer = 0;
}
