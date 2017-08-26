#include "dev_t.h"
#include <string.h>
#include <stdio.h>


void devt_init(void)
{
    memset(minors, 0, sizeof(int)*MAX_DEVICE_TYPE);
    memset(type2major_table, 0, sizeof((void*)0)*MAX_DEVICE_TYPE);
    type2major_mapping();
}


/**
 *  输入：无
 *  输出：无
 *  功能：将设备类型与其对应的主设备号之间建立联系，使得通过设备类型能够快速
 *  找到对应的主设备号
 *  说明：键值对(device type, major)
 */ 
static void type2major_mapping(void)
{
    int major;
    long value;
    const void* key;

    for (major=first_used_major; major<first_unused_major; major++){
        value = (long)major;
        key = (const void*)device_type[major];

        add_hash_item(key, value, type2major_table, PRIME_TABLSIZ);
    } 
}


/**
 *　输入：设备的类型dev_type
 *  输出：设备号
 *  功能：根据传入设备的类型，为该设备分配一个设备号
 */ 
devno_t alloc_devno(char* dev_type)
{
    int major;
    int minor;
    devno_t devno;

    major = type2major(dev_type);
    minor = minors[major]++;
    devno = MAKE_DEV(major, minor);
#if DEBUG    
    printf("device type: %s  major: %d minor:  %d\n", dev_type, major, minor);
#endif
    return devno;
}


int get_first_used_major(void)
{
    return first_used_major;
}


int get_first_unused_major(void)
{
    return first_unused_major;
}


/**
 *　输入：设备的类型dev_type
 *　输出：设备的主设备号
 *　功能：根据设备的类型，返回对应的主设备号
 */ 
int type2major(char* dev_type)
{
    int major;
    struct hash_item* hip;

    hip = get_hash_item(dev_type, type2major_table, PRIME_TABLSIZ);
    if (hip == NULL) return -1;


    major = (int)hip->value;

    return major;
}


char* major2type(int major)
{
    return device_type[major];
}
