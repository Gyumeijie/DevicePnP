#ifndef DRIVER_H
#define DRIVER_H

//系统所支持的最大设备类型数
#define MAX_DEVICE_TYPE 256 

typedef char interface_t[32];

//定义设备驱动结构体
struct driver{
  interface_t interface;   
  void* device_operation;
  int (*match)(void);
};

//定义设备驱动索引表节点
struct driver_node{
   struct driver* drip;
   struct driver_node* next; 
};


//定义设备驱动索引表
static struct driver_node* driver_index_table[MAX_DEVICE_TYPE];

//初始化driver_index_table
extern void driver_init(void);

//添加向设备驱动索引表设备驱动结构体(设备驱动注册模块)
extern int add_driver(int index, struct driver* drip);

//添加设备索引表节点
static void add_driver_node(struct driver_node** head, struct driver_node* node);

//获取支持给定接口的设备驱动(设备驱动绑定模块)
extern struct driver* get_driver(int index, interface_t interface);
#endif
