#include "magnetometer_getxyz.h" 

//使用unsigned int*类型的数据，使用ad接口
int magnetometer_getxyz_template0(void* para_struct, void* data) 
{
    //在这一层对data的类型具体化
    return magnetometer_read_helper0(para_struct, (unsigned int*)data);
}

