#include "adda_operation.h"
#include "magnetorquer_write_helper.h"
#include <stdio.h>

int magnetorquer_write_helper0(void* para_struct, void* data)
{
    struct plain_array* set_pat0p = para_struct;
    unsigned int len = set_pat0p->len;
    unsigned int* arr = set_pat0p->arr;

    return da_devices_write(data, len, arr);
}
