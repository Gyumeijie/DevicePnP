#include "command_sequence_fill.h"
#include "flywheel_match.h"
#include "flywheel_open.h"
#include <stdio.h>

int flywheel_open_template0(void* para_struct, void* para)
{ 
    // 对于open函数而言（暂时还没实现）计算函数可能还没有
    fill_cmd_seq_dynamically(para, para_struct);
}


