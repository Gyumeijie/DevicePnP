#include "adda_operation.h"
#include "magnetometer_read_helper.h"
#include <stdio.h>

int magnetometer_read_helper0(void* para_struct, void* data)
{
    struct plain_array* get_pat0p = para_struct;
    unsigned int len = get_pat0p->len;
    unsigned int* arr = get_pat0p->arr;

    return ad_devices_read(data, len, arr);
}

