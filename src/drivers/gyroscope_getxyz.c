#include "gyroscope_getxyz.h"

//使用unsigned int*类型的数据，使用i2c接口
int gyroscope_getxyz_template0(void* para_struct, void* data)
{
    //在这一层开始对data的类型具体化
    return gyroscope_read_helper0(para_struct, (unsigned int*)data);
}

