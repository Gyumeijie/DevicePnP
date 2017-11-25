#include "interpreter.h"

/**
 *  这里新建一个interpreter文件是将解析器内部的实现细节屏蔽掉,
 *  向外提供一个更抽象的接口
 */

void interpreter_init()
{
    parser_init();
    executor_init();
}
