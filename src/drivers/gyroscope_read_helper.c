#include "gyroscope_read_helper.h"
#include <stdio.h>

int gyroscope_read_helper0(void* para_struct, void* data)
{
    struct get_reg_pattern0* getreg_pat0p = para_struct;
    char reg_address = getreg_pat0p->reg_address;
    int size = getreg_pat0p->size;

    //TODO 模拟i2c读寄存器函数
    printf("address: 0x%02x size:%d\n", reg_address, size);
    *(unsigned int*)data = reg_address;
    return size;
}

