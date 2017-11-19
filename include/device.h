#ifndef DEVICE_H
#define DEVICE_H

#define MAX_DEVICE_TYPE 256 //系统所支持的最大设备类型数
#define PRIME_TABLSIZ 251  //定义哈希表的大小
#define MAX_DEVICES 256 //系统所能挂载的最大设备数 

#include "dev_t.h"
#include "hashstr.h"


//定义设备结构体
struct device{
  devno_t devno;   
  char interface[32];
  char lid[32];
  char type[32];
  void* device_operation;
  void* private_data;
};

//定义设备索引表节点
struct device_node{
   struct device* devp;
   struct device_node* next; 
};

//记录设备索引表中节点的个数
static unsigned int device_num;

//定义设备索引表
static struct device_node* device_index_table[MAX_DEVICE_TYPE];

//定义设备逻辑标识符与设备结构体指针的转换表
static struct hash_item* lid2dev_table[MAX_DEVICES];

//添加设备索引表节点
static void add_device_node(struct device_node** head, struct device_node* node);

//初始化device_index_table和lid2dev_table
extern void device_init(void);

//利用哈希函数在转化表中将设备结构体指针填入到设备逻辑标识符
//对应的槽位(设备注册模块)
extern void lid2dev_mapping(const char* lid, struct device* devp);

//添加向设备索引表设备结构体(设备注册模块)
extern void add_device(int index, struct device* devp);

//通过设备逻辑标识符查找给定的设备结构体(设备打开模块)
extern struct device* find_device(const char* lid);

//遍历设备索引表(设备驱动绑定模块)
extern struct device* get_device(void);

//返回device_num(设备驱动绑定模块)
extern unsigned int get_device_num(void);

#endif
