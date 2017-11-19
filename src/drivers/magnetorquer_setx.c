#include "magnetorquer_setx.h" 
#include "magnetorquer_write_helper.h" 

//使用unsigned int*类型的数据，使用da接口
int magnetorquer_setx_template0(void* para_struct, void* data) 
{
    //在这一层开始对data的类型具体化
    return magnetorquer_write_helper0(para_struct, (unsigned int*)data);
}

