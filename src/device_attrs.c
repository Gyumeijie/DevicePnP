#include "device_attrs.h"


void* get_device_attrs_item(void)
{
     static int  counter = 0;
     
     if (counter < attrs_item_num){
           return (void*)&attrs_items[counter++];
     }else{
           counter = 0;
           return NULL;
     }
}


unsigned int get_attrs_item_num(void)
{
    return attrs_item_num;
}


char* get_device_lid(void* attrs)
{
    return ((struct device_attrs*)attrs)->lid;
}


char* get_device_type(void* attrs)
{
    return ((struct device_attrs*)attrs)->type;
}


char* get_device_interface(void* attrs)
{
    return ((struct device_attrs*)attrs)->interface;
}
