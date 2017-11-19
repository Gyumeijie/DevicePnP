#include "command_sequence_fill.h"
#include "flywheel_match.h"
#include "flywheel_open.h"
#include <stdio.h>

int flywheel_open_template0(void* para_struct, void* para)
{ 
    struct command_sequence* open_template0 = para_struct;
    fill_cmd_seq_dynamically(open_template0, para);
}


