#include "command_sequence_fill.h"
#include "flywheel_match.h"
#include <stdio.h>

int flywheel_set_speed_template0(void* para_struct, void* para)
{
    struct command_sequence* set_speed_template0 = para_struct;
    fill_cmd_seq_dynamically(set_speed_template0, para);

    int bytes_size =  set_speed_template0->bytes_size;
    int i;
    for (i=0; i<bytes_size; i++){
       printf("0x%02X  ", set_speed_template0->bytes_value[i]);
       printf("%s \n", set_speed_template0->cmd_seq_desc[i].occupied_by);
    }
}

