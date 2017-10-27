#ifndef HANDLE_EVENT_H_
#define HANDLE_EVENT_H_
#include "handle_event_func.h"
#include "event.h"
#include "unistd.h"
#include<pthread.h>
#define REPOS_MAX_LEN 20
static void* p_repos_array[REPOS_MAX_LEN];
static UINT is_repos_avail[REPOS_MAX_LEN]={0};
void init_event_repos_array(void);
void get_one_event_repos(UINT* pos);
bool get_one_event(void* p_repos,void* p_evt_node);
void handle_event(void* p_event);
void* get_evt_repos(UINT pos);
void* evt_repos_scan_pthread_func(void* argc);
void create_evt_repos_scan_unit(void);
void throw_event(UINT repos_id,char* RT_lid,EVT_TYPE event_type);
#endif

