#include "device_open.h"
#include "device.h"
#include <malloc.h>
#include <string.h>
#include <stdio.h>

 
void device_open_init(void)
{
     memset(device_open_index_table, 0, sizeof((void*)0)*MAX_DEVICES_OPEN);
     memset(lid2idx_table, 0, sizeof((void*)0)*MAX_DEVICES_OPEN);
}


int open_device(char* lid, open_status* os)
{
    int already_open;
    int index;
    struct device_open* devop = NULL;

    already_open = has_already_open(lid);    
    //判断该设备是否已经打开
    if (already_open){
        index = get_index_by_lid(lid);
        //设置设备打开状态
        *os = ALREADY_OPEN;
        return index;
    }

    //获取设备打开索引表空闲的表项
    index = get_unused_index();
    if (index == -1) return -1;
    
    //分配设备打开结构体
    devop = (struct device_open*)malloc(sizeof(struct device_open));
    if (devop == NULL) return -1;
    devop->lid = lid;
   
    //建立设备打开结构体与设备结构体之间的联系
    attatch_device(devop);

    //将设备打开结构体指针填入到设备打开索引表中
    device_open_index_table[index] = devop;
    
    //建立设备逻辑标识符与相应设备打开表表项下标的联系
    lid2idx_mapping(lid, index);
   
    //设置设备打开状态
    *os = NEWLY_OPEN;
    return index;
}


void release_device(int index)
{
    struct device_open* devop = NULL;
    char* lid = NULL;

    devop =  device_open_index_table[index];
    lid = devop->lid;

    lid2idx_mapping(lid, -1);
    free(devop);
}

/**
 *　输入：设备打开结构体指针devop
 *　输出：无
 *　功能：将设备打开结构体与设备索引表中的设备结构体建立连接
 */
static void attatch_device(struct device_open* devop)
{
    struct device* devp = NULL;
    //根据设备逻辑号找到相应的设备结构体
    devp = find_device(devop->lid);
    
    devop->device_operation = devp->device_operation;
    devop->private_data = devp->private_data;
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
    int index;
    index = get_index_by_lid(lid);
    
    return (index == -1) ? 0 : 1;
}


/**
 *　输入：设备逻辑标识符lid和对应的设备打开索引表表项下标index
 *　输出：无
 *  功能：建立设备逻辑标识符和对应的设备打开索引表表项下标之间的联系
 *  说明：键值对(lid,index)
 */ 
static void lid2idx_mapping(const char* lid, int index)
{
     long value = (long)index;
     const void* key = (const void*)lid;

     add_hash_item(key, value, lid2idx_table, PRIME_TABLSIZ);
}


static int get_index_by_lid(char* lid)
{
    int index;
    struct hash_item* hip;

    hip = get_hash_item(lid, lid2idx_table, PRIME_TABLSIZ);
    if (hip == NULL) return -1;
    
    index = (int)hip->value;
    return index;
}


struct device_open* get_device_open_struct(int index)
{
   return device_open_index_table[index];
}
