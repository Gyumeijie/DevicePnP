#include "device_open.h"
#include "device.h"
#include "error_report.h"
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
        int index = get_index_by_lid(lid);
        // 设置设备打开状态
        *os = ALREADY_OPEN;
        return index;
    }

    // 获取设备打开索引表空闲的表项
    int index = get_unused_index();
    if (index == -1) return -1;
    
    struct device_open* devop = malloc(sizeof(struct device_open));
    if (devop == NULL) return -1;
    devop->lid = lid;
   
    // 建立设备打开结构体与设备结构体之间的联系
    if(! attach_device(devop, dev_type)) {
       free(devop);
       return -1;
    }

    // 将设备打开结构体指针填入到设备打开索引表中
    device_open_index_table[index] = devop;
    
    // 建立设备逻辑标识符与相应设备打开表表项下标的联系
    lid2idx_mapping(lid, index);
   
    // 设置设备打开状态
    *os = NEWLY_OPEN;

    return index;
}


void release_device(int index)
{
    struct device_open* devop = device_open_index_table[index];

    lid2idx_mapping(devop->lid, -1);

    free(devop);
}


/**
 *　输入：设备打开结构体指针devop
 *　输出：无
 *　功能：将设备打开结构体与设备索引表中的设备结构体建立连接
 */
static int attach_device(struct device_open* devop, const char* dev_type)
{
    // 根据设备逻辑号找到相应的设备结构体
    struct device* devp = find_device(devop->lid);
    if(!check_null(__FILE__, __func__, "devp", devp)){
       printf("Detail: can't find device named '%s' in register table\n",
                                                devop->lid);   
       return FAILURE;
    } 
    
    devop->type = devp->type;
    if (!check_device_type(devop, dev_type)) return FAILURE;

    devop->device_operation = devp->device_operation;
    devop->private_data = devp->private_data;
    
    return SUCCESS;
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
    int index = get_index_by_lid(lid);
    
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


static int get_index_by_lid(const char* lid)
{

    struct hash_item* hip = get_hash_item(lid, lid2idx_table, PRIME_TABLSIZ);
    if (hip == NULL) return -1;
    
    return  (int)hip->value;
}


struct device_open* get_device_open_struct(int index)
{
   return  device_open_index_table[index];
}


int check_device_type(struct device_open* devop, const char* dev_type)
{
    if (strcmp(devop->type, dev_type)){
       char msg[256];
       sprintf(msg, "can't not use %s operation to operate %s with type %s",
                     dev_type, devop->lid, devop->type);
       report_error(__FILE__, __func__, msg);
       return FAILURE;
    }
    
    return SUCCESS;
}
