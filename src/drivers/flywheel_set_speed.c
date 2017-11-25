#include "command_sequence_fill.h"
#include "flywheel_match.h"
#include <stdio.h>

int flywheel_set_speed_template0(void* para_struct, void* para)
{
    fill_cmd_seq_dynamically(para, para_struct);

    struct command_sequence* cmd_seq = para_struct;
    int bytes_size = cmd_seq->bytes_size;
    int i;
    for (i=0; i<bytes_size; i++){
       printf("0x%02X  ", cmd_seq->bytes_value[i]);
       printf("%s \n", cmd_seq->cmd_seq_desc[i].occupied_by);
    }
}

