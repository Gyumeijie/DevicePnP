/*
 *声明交通灯结构。
 */
#ifndef TRAFFIC_H_
#define TRAFFIC_H_
#include "handle_data_package.h"
#include "address_map.h"
#define TRAFFIC_STATUS UINT
#define UNCHECKED 4
#define GREEN 1
#define YELLOW 2
#define RED 3
#define IS_BACK UINT
#define NOT_BACK 2
#define BACK 1
#define IS_LOADED UINT
#define LOADED 1
#define NOT_LOADED 2
#define TRAFFIC_ENABLE 1
#define TRAFFIC_DISABLE 0
#define TRAFFIC_REPOS_MAX_LEN 100 
#define TRAFFIC_LIST_MAX_LEN 32
#define PRIORITY_LOW 1
#define PRIORITY_HIGH 2 
#define NOT_SET -2

typedef struct traffic_light{
    char* dev_lid;
    TRAFFIC_STATUS traffic_status;
    IS_LOADED is_loaded;
    IS_BACK is_back;
    UINT count;
}traffic_light;

typedef struct traffic_light_repos{
    traffic_light* p_traffic_light_list[TRAFFIC_LIST_MAX_LEN];
    UINT list_len;
    char* RT_lid_array[TRAFFIC_LIST_MAX_LEN];
    UINT RT_section_priority[TRAFFIC_LIST_MAX_LEN];
    UINT dev_num[TRAFFIC_LIST_MAX_LEN];
    bool is_traffic_enable;
    UINT scan_pos;
}traffic_light_repos;
void* create_traffic_repos(char* bus_type,char* bus_lid);//模拟交通灯控制以总线为单位
#endif

