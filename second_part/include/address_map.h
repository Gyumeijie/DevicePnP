/*
 * address_map.h，三级索引表结构用来管理逻辑标示符与转发地址
 * 之间的映射,第一级索引表使用设备逻辑标识符标识，第二级索引
 * 表使用RT逻辑标识符标识，第三级索引表使用总线标识符标识。
 */
#ifndef ADDRESS_MAP_H_
#define ADDRESS_MAP_H_
#include "handle_data_package.h"
#include "relevant_struct_def.h"
#include "handle_event.h"
#define F_INDEX_LIST_MAX_LEN 5
#define S_INDEX_LIST_MAX_LEN 32
#define T_INDEX_LIST_MAX_LEN 20
#define T_INDEX_LIST_MAX_NUM 160
#define S_INDEX_LIST_MAX_NUM 5
#define READ_REGION_MAX_SIZE 0x400
#define WRITE_REGION_MAX_SIZE 0X400
typedef struct t_index_node{
    char dev_lid[ATTR_LID_VALUE_MAX_LEN];
    dataNode* addr_read_s;
    dataNode* addr_read_e;
    dataNode* addr_work_r;
    dataNode* addr_write_s;
    dataNode* addr_write_e;
    dataNode* addr_work_w;
}t_index_node;
typedef struct t_index_list{
    UINT t_node_len;
    t_index_node t_node[T_INDEX_LIST_MAX_LEN];
}t_index_list;
typedef struct s_index_node{
    char RT_lid[ATTR_LID_VALUE_MAX_LEN];
    t_index_list* t_list_p;
}s_index_node;
typedef struct s_index_list{
    UINT s_node_len;
    s_index_node s_node[S_INDEX_LIST_MAX_LEN];
}s_index_list;
typedef struct f_index_node{
    char bus_type[ATTR_TYPE_VALUE_MAX_LEN];
    char bus_lid[ATTR_LID_VALUE_MAX_LEN];
    s_index_list* s_list_p;
}f_index_node;
typedef struct f_index_list{
    UINT f_node_len;
    f_index_node f_node[F_INDEX_LIST_MAX_LEN];
}f_index_list;
static f_index_list index_list_f;
static s_index_list index_list_s[S_INDEX_LIST_MAX_NUM];
static UINT index_list_s_len=0;
static t_index_list index_list_t[T_INDEX_LIST_MAX_NUM];
static UINT index_list_t_len=0;
void create_index_list(void);
bool is_write_region_empty(char* bus_type,char* bus_lid,char* RT_lid,char* dev_lid);
bool is_read_region_empty(char* bus_type,char* bus_lid,char* RT_lid,char* dev_lid);
UINT get_write_region_size(char* bus_type,char*bus_lid,char* RT_lid,char* dev_lid);
UINT get_read_region_size(char* bus_type,char*bus_lid,char* RT_lid,char* dev_lid);
void dev_read_data(char* bus_type,char* bus_lid,char* RT_lid,char* dev_lid,void* buffer,UINT readSize,UINT* size);
void dev_write_data(char* bus_type,char* bus_lid,char* RT_lid,char*dev_lid,void* Buffer,UINT writeSize,UINT* size);
void app_read_data(char* bus_type,char* bus_lid,char* RT_lid,char* dev_lid,void* buffer,UINT readSize,UINT* size);
void app_write_data(char* bus_type,char* bus_lid,char* RT_lid,char*dev_lid,void* dataBuffer,UINT writeSize,UINT* size);
void* get_t_index_node(char* bus_type,char* bus_lid,char* RT_lid,char* dev_lid);
void* get_read_addr_s(void* t_index_node);
void* get_read_addr_e(void* t_index_node);
void* get_read_addr_work_p(void* t_index_node);
void* get_write_addr_s(void* t_index_node);
void* get_write_addr_e(void* t_index_node);
void* get_write_addr_work_p(void* t_index_node);
UINT get_s_index_list_len(char* bus_type,char* bus_lid);
void* get_t_index_list(char* bus_type,char* bus_lid,UINT pos);
void* get_s_index_list(char* bus_type,char* bus_lid);
UINT get_t_index_list_len(void* p_t_index_list);
void get_t_index_node_lid(void* p_t_index_list,UINT pos,char** p_dev_lid);
void get_s_index_node_lid(void* p_s_index_list,UINT pos,char** p_RT_lid);
void set_index_node_pointer(void* t_index_node_p,bool isRead,void* e_p,void* s_p,void* w_p);
#endif

