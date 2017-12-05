#ifndef DEVICE_OPEN_H
#define DEVICE_OPEN_H

#include "hashstr.h"
#include "driver.h"

#define MAX_DEVICES_OPEN 256 // 系统所支持的最大的打开设备数
#define PRIME_TABLSIZ 251 // 定义哈希表的大小

// 定义设备的打开状态
typedef enum {NEWLY_OPEN, ALREADY_OPEN} open_status;

// 定义设备打开索引表
static struct device* device_open_index_table[MAX_DEVICES_OPEN];

// 逻辑标识符到设备打开索引表表项的映射表
static struct hash_item* lid2idx_table[MAX_DEVICES_OPEN];

extern int  open_device(char* lid, open_status* os, const char* dev_type);

extern void device_open_init(void);

extern void release_device(int index);

static void lid2idx_mapping(const char* lid, int index);

static int  get_open_index(const char* lid);

static int get_unused_index(void);

static int has_already_open(char* lid);

extern struct device* get_open_device(int index);

extern int check_device_type(struct device* devp, const char* dev_type);

#endif 
