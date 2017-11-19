#include "adda_operation.h"
#include "analogsunsensor_read_helper.h"
#include <stdio.h>

int analogsunsensor_read_helper0(void* para_struct, void* data)
{
    struct plain_array* read_template0 = para_struct;
    unsigned int len = read_template0->len;
    unsigned int* arr = read_template0->arr;

    return ad_devices_read(data, len, arr);
}

