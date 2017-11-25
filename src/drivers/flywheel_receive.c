#include "flywheel_receive.h"
#include "bytes_array_assembly.h"
#include "flywheel_match.h"
#include <stdio.h>

//TODO para_struct 和 para更好的命名
//para_struct是数据模板结构，而para是上面传递下来的参数
int flywheel_receive_template0(void* para_struct, void* para)
{
    static char bytesdata[16] = {
        0x00, 0x01, 0x02, 0x03, 0x00, 0x14, 0x00, 0x00,
        0x00, 0x28, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
    };

    return do_bytes_array_assembly(bytesdata, 16, para, para_struct); 
}

