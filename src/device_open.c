#include "device_open.h"
#include "device.h"
#include "error_report.h"
#include "miscellaneous.h"
#include <malloc.h>
#include <string.h>
#include <stdio.h>

 
void device_open_init(void)
{
   memset(device_open_index_table, 0, sizeof((void*)0)*MAX_DEVICES_OPEN);
   memset(lid2idx_table, 0, sizeof((void*)0)*MAX_DEVICES_OPEN);
}


int open_device(char* lid, open_status* os, const char* dev_type)
{
   int already_open = has_already_open(lid);    
   if (already_open){
      int index = get_open_index(lid);
       
       // 设置设备打开状态
       *os = ALREADY_OPEN;
       return index;
   }

   // 获取设备打开索引表空闲的表项
   int index = get_unused_index();
   if (index == -1) return -1;

   struct device* devp = find_device(lid);
   assure_not_null(__FILE__, __func__, "devp", devp);
   
   // 将设备结构体指针填入到设备打开索引表中
   device_open_index_table[index] = devp;
   
   // 建立设备逻辑标识符与相应设备打开表表项下标的联系
   lid2idx_mapping(lid, index);
  
   // 设置设备打开状态
   *os = NEWLY_OPEN;

   return index;
}


static int get_unused_index(void)
{  
   int i;
   for (i=0; i<MAX_DEVICES_OPEN; i++){
       if (device_open_index_table[i] == NULL){
           return i;
       }
   }

   return -1;
}


static int has_already_open(char* lid)
{
   int index = get_open_index(lid);
  
   return (index == -1) ? 0 : 1;
}


// 建立设备逻辑标识符和对应的设备打开索引表表项下标之间的联系
// 为了方便后面通过设备逻辑号lid查找设备打开索引表下标
static void lid2idx_mapping(const char* lid, int index)
{
   long value = (long)index;
   const void* key = (const void*)lid;

   add_hash_item(key, value, lid2idx_table, PRIME_TABLSIZ);
}


static int get_open_index(const char* lid)
{
   struct hash_item* hip = get_hash_item(lid, lid2idx_table, PRIME_TABLSIZ);

   // 这里不能去保证hip不为null, 如果是has_already_open调用的就
   // 有可能为null, 所以不能使用assure_not_null
   if (hip == NULL) return -1;
   
   return  (int)hip->value;
}


struct device* get_open_device(int index)
{
   return  device_open_index_table[index];
}


int check_device_type(struct device* devp, const char* dev_type)
{
   if (is_not_equal(devp->type, dev_type)){
      char msg[256];
      
      sprintf(msg, "can't not use %s operation to operate %s with type %s",
                    dev_type, devp->lid, devp->type);
      fprintf(stderr, "%s", msg);

      return FAILURE;
   }
   
   return SUCCESS;
}
