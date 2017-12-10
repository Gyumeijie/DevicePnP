#include "gyroscope_write_helper.h"
#include <stdio.h>

int gyroscope_write_helper0(void* para_struct, void* data)
{
    struct register_array* open_template0 = para_struct;
    int len = open_template0->len;
    struct reg* regp = open_template0->regp;

    //TODO i2c写寄存器函数
    int i;
    for (i=0; i<len; i++){
       char reg_address = regp[i].addr;
       char val = regp[i].val;
       printf("address: 0x%02x value:0x%02x\n", reg_address, val);
    }
}
