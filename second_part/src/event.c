#include "event.h"
void* create_evt_repos(void){
    evt_repository* p_evt_repos=(evt_repository*)malloc(sizeof(evt_repository));
    evt* p_list=(evt*)malloc((EVT_LIST_MAX_LEN)*sizeof(evt));
    p_evt_repos->p_evt_list=p_list;
    p_evt_repos->list_size=EVT_LIST_MAX_LEN;
    p_evt_repos->counter=0;
    p_evt_repos->global_enable=ENABLE;
    p_evt_repos->start_pos=0;
    p_evt_repos->end_pos=0;
    return(void*)p_evt_repos;
}
bool insert_evt_node(void* p_evt_repos,EVT_TYPE event_type,char* sel_RT_lid){
    evt_repository* p_evt_repos_tmp=(evt_repository*)p_evt_repos;
    if(p_evt_repos_tmp==NULL)return false;
    if((p_evt_repos_tmp->end_pos+1)%p_evt_repos_tmp->list_size==p_evt_repos_tmp->start_pos){
        return false;
    }//留一格
    else{
        UINT insert_pos=p_evt_repos_tmp->end_pos;
        evt* p_evt_list_tmp=p_evt_repos_tmp->p_evt_list;
        get_current_time((void*)&((p_evt_list_tmp+insert_pos)->time_stamp));
        (p_evt_list_tmp+insert_pos)->event_type=event_type;
        (p_evt_list_tmp+insert_pos)->sel_RT_lid=sel_RT_lid;
        p_evt_repos_tmp->counter++;
        p_evt_repos_tmp->end_pos=(insert_pos+1)%p_evt_repos_tmp->list_size;
    }
    return true;
}
bool delete_evt_node(void* p_evt_repos,void* p_evt_node){
    evt_repository* p_evt_repos_tmp=(evt_repository*)p_evt_repos;
    if(p_evt_repos_tmp->counter==0)return false;
    evt* p_evt_list_tmp=p_evt_repos_tmp->p_evt_list;
    UINT delete_pos=p_evt_repos_tmp->start_pos;
    if(p_evt_repos_tmp==NULL)return false;
    if(p_evt_repos_tmp->start_pos==p_evt_repos_tmp->end_pos)return false;
    else{
        memcpy(p_evt_node,(void*)(p_evt_list_tmp+delete_pos),sizeof(evt));
        p_evt_repos_tmp->counter--;
        p_evt_repos_tmp->start_pos=(p_evt_repos_tmp->start_pos+1)%p_evt_repos_tmp->list_size;
    }
    return true;
}
void reset_evt_repos(void* p_evt_repos){
    if(p_evt_repos==NULL)return;
    evt_repository* p_evt_repos_tmp=(evt_repository*)p_evt_repos;
    p_evt_repos_tmp->start_pos=0;
    p_evt_repos_tmp->end_pos=0;
    p_evt_repos_tmp->counter=0;
    p_evt_repos_tmp->global_enable=ENABLE;
}
bool append_event_node(void* p_RT_evt_repos,char* sel_RT_lid,EVT_TYPE event_type){
    evt_repository* p_evt_repos_tmp=(evt_repository*)p_RT_evt_repos;
    bool isSucceed=insert_evt_node(p_evt_repos_tmp,event_type,sel_RT_lid);
    return isSucceed;
}
bool get_event_node(void* p_evt_repos,void* p_evt_node){
    evt_repository* p_evt_repos_tmp=(evt_repository*)p_evt_repos;
    bool isSucceed=delete_evt_node(p_evt_repos_tmp,p_evt_node);
    return isSucceed;
}

void set_evt_repos_global_enable(void* p_evt_repos){
    evt_repository* p_evt_repos_tmp=(evt_repository*)p_evt_repos;
    p_evt_repos_tmp->global_enable=ENABLE;
}
void* get_evt_node_time(void* p_evt_node){
    return (void*)(&((evt*)p_evt_node)->time_stamp);
}
UINT get_evt_node_event_type(void* p_evt_node){
    return ((evt*)p_evt_node)->event_type;
    
}
char* get_evt_node_sel_RT_lid(void* p_evt_node){
    return ((evt*)p_evt_node)->sel_RT_lid;

}
