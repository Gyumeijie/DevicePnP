#include "driver_loaders.h"
#include <stdio.h>


unsigned int get_driver_loader_num(void)
{
    return driver_loader_num;
}


driver_loader get_driver_loader(void)
{
    static int  counter = 0;

    if (counter < driver_loader_num){
        return driver_loaders_table[counter++];
    }else{
        counter = 0;

        return NULL;
    }
}

