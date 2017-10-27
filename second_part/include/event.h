#ifndef EVENT_H_
#define EVENT_H_
#include "relevant_struct_def.h"
#include "event_type.h"
#include "bool.h"
#define EVT_TYPE UINT
#define EVT_LIST_MAX_LEN 128
#define REPOS_TYPE_1553_RET 1
#define REPOS_TYPE_1553 2
#define REPPOS_TYPE_RT 3
#define REPOS_TYPE UINT
#define ENABLE 1
#define DISABLE 0

typedef struct event{
    timeStamp time_stamp;
    EVT_TYPE event_type;
    char* sel_RT_lid;
}evt;
typedef struct event_repository{
    evt* p_evt_list;
    UINT list_size;
    UINT counter;
    UINT global_enable;
    UINT start_pos;
    UINT end_pos;
}evt_repository;
void* create_evt_repos(void); //注册一个event_repository,系统默认一个事件库即可
bool insert_evt_node(void* p_evt_repos,EVT_TYPE event_type,char* sel_RT_lid);
bool delete_evt_node(void* p_evt_repos,void* p_evt_node);
void reset_evt_repos(void* p_evt_repos);
bool append_event_node(void* p_evt_repos,char* RT_lid,EVT_TYPE event_type);
bool get_event_node(void* p_evt_repos,void* p_evt_node);
void* get_evt_node_time(void* p_evt_node);
UINT get_evt_node_event_type(void* p_evt_node);
char* get_evt_node_sel_RT_lid(void* p_evt_node);
void set_evt_repos_global_enable(void* p_evt_repos);
#endif
