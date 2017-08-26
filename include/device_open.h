#ifndef DEVICE_OPEN_H
#define DEVICE_OPEN_H

#include "hashstr.h"

#define MAX_DEVICES_OPEN 256 //系统所支持的最大的打开设备数
#define PRIME_TABLSIZ 251 //定义哈希表的大小

//定义设备打开结构体
struct device_open{   
  char *lid;  
  void* device_operation;
  void* private_data;
};

//定义设备的打开状态
typedef enum {NEWLY_OPEN, ALREADY_OPEN} open_status;

//定义设备打开索引表
static struct device_open* device_open_index_table[MAX_DEVICES_OPEN];

//逻辑标识符到设备打开索引表表项的映射表
static struct hash_item* lid2idx_table[MAX_DEVICES_OPEN];

extern int  open_device(char* lid, open_status* os);

extern void device_open_init(void);

extern void release_device(int index);

static void lid2idx_mapping(const char* lid, int index);

static int  get_index_by_lid(char* lid);

static int get_unused_index(void);

static void attatch_device(struct device_open* devop);

static int has_already_open(char* lid);

extern struct device_open* get_device_open_struct(int index);

#endif 
