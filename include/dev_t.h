#ifndef DEV_T_H
#define DEV_T_H

#include "hashstr.h"

#define MAX_DEVICE_TYPE 256
#define PRIME_TABLSIZ 251 //定义哈希表大小
#define MINORBITS 24 //次设备号位数
#define MINORMASK ((1U << MINORBITS) -1) //次设备号掩码
#define GET_MAJOR(dev) ((dev) >> MINORBITS) // 从设备号中获取主设备号
#define GET_MINOR(dev) ((dev) & MINORMASK) // 从设备号中获取次设备号
#define MAKE_DEV(major, minor) (((major) << MINORBITS) | (minor)) //生成设备号

typedef unsigned int devno_t;

//预定义设备的主设备号
static char device_type[MAX_DEVICE_TYPE][20] = {

"", "", "", "", "", "", "", "", "", "", //0-9保留
"analogsunsensor", //10 模拟式太阳敏感器
"magnetometer",    //11 磁强计
"starsensor",      //12 星敏感器
"flywheel",        //13 飞轮
"gyroscope",       //14 陀螺仪
"horizonsensor",   //15 地平仪
"magnetorquer",    //16 磁力矩器 
};


//记录每类设备的次设备号的分配情况，每分配一个则相应的加1
static int minors[MAX_DEVICE_TYPE];

static int first_unused_major = 17;

static int first_used_major = 10;

//设备类型到主设备号快速索引表
static struct hash_item* type2major_table[MAX_DEVICE_TYPE];

//根据设备类型申请设备号
extern devno_t alloc_devno(char* dev_type);

//初始化type2major_table
extern void devt_init(void);

//利用哈希函数在type2major_table中将主设备号填入到设备类型对应的槽位
static void type2major_mapping(void); 

extern int get_first_used_major(void);

extern int get_first_unused_major(void);

//根据设备的类型，返回对应的主设备号
extern int type2major(char* dev_type);

//根据设备的主设备号，返回设备类型(设备驱动绑定模块)
extern char* major2type(int major);

#endif
