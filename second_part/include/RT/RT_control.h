/*
 * 定义几个接受字符串的缓存,假设RT下最多可以挂载31个设备
 */
#ifndef RT_CONTROL_H_
#define RT_CONTROL_H_
#include "relevant_struct_def.h"
#include "handle_data_package.h"
#include "config_1553.h"
#include "route_map.h"
#include "my_socket.h"
#include <unistd.h>
#define BC_device_num 1
//#define RT_physical_addr 9000//具体再改
#define MOUNT_DEV_MAX_NUM 31
#define CACHE_MAX_SIZE 0x400 //1k
#define READ_MAX_SIZE_RT 0x40
#define RT_DATA_BLOCK_VALID_PREFIX (unsigned char)0x80
static UINT s_pos[MOUNT_DEV_MAX_NUM]={0};
static UINT e_pos[MOUNT_DEV_MAX_NUM]={0};
static unsigned char write_buffer[MOUNT_DEV_MAX_NUM][CACHE_MAX_SIZE]={0};
static UINT child_port_array[MOUNT_DEV_MAX_NUM]={0};
static UINT len=0;
void init_port_array(UINT RT_physical_addr);
void clear_write_buffer(void);
void write_write_buffer(UINT child_port,unsigned char* buffer,UINT write_size,UINT* size);
void read_write_buffer(UINT pos,unsigned char* buffer,UINT read_size,UINT* size);
void pack_package(unsigned char* buffer,UINT* buffer_size);
int get_child_port_pos(UINT child_port);
UINT get_child_port(int pos);
UINT get_child_port_array_len(void);
#endif
