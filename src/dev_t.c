#include "dev_t.h"
#include "error_report.h"
#include <string.h>
#include <stdio.h>


void devt_init(void)
{
   memset(minors, 0, sizeof(int)*MAX_DEVICE_TYPE);
   memset(type2major_table, 0, sizeof((void*)0)*MAX_DEVICE_TYPE);
   type2major_mapping();
}


// 将设备类型与其对应的主设备号之间建立联系
// 使得通过设备类型能够快速查询到主设备号
static void type2major_mapping(void)
{
   int major;
   for (major=first_used_major; major<first_unused_major; major++){
      long value = (long)major;
      const void* key = (const void*)device_type[major];

      add_hash_item(key, value, type2major_table, PRIME_TABLSIZ);
   } 
}


devno_t alloc_devno(char* dev_type)
{
   int major = type2major(dev_type);
   int minor = minors[major]++;
   
   return MAKE_DEV(major, minor);
}


int get_first_used_major(void)
{
   return first_used_major;
}


int get_first_unused_major(void)
{
   return first_unused_major;
}


// 根据设备的类型，返回对应的主设备号
int type2major(char* dev_type)
{
   struct hash_item* hip;
   hip = get_hash_item(dev_type, type2major_table, PRIME_TABLSIZ);
   assure_not_null(__FILE__, __func__, "hip", hip);

   return  (int)hip->value;
}


// 根据主设备号，返回对应的设备的类型
char* major2type(int major)
{
    return device_type[major];
}
