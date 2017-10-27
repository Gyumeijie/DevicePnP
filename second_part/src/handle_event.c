#include "handle_event.h"
void init_event_repos_array(){
    printf("初始化事件库仓库...\n");
    int i=0;
    for(;i<REPOS_MAX_LEN;i++){
        if(p_repos_array[i]!=NULL){
            free(p_repos_array[i]);
        }
        void* p_repos_tmp=create_evt_repos();
        p_repos_array[i]=p_repos_tmp;
        is_repos_avail[i]=1;
    }
    printf("初始化事件库仓库结束...\n");
}
void get_one_event_repos(UINT* pos){
    int i=0;
    for(;i<REPOS_MAX_LEN;i++){
        if(is_repos_avail[i]==1){
            is_repos_avail[i]=0;
            *pos=i;
            printf("获取编号为%d的事件库...\n",i);
            return;
        }
    }
}
bool get_one_event(void* p_repos,void* p_evt_node){
    evt_repository* p_evt_repos_tmp=(evt_repository*)p_repos;
    void* p_evt_node_tmp=(evt*)p_evt_node;
    bool is_get_true=get_event_node(p_repos,p_evt_node_tmp);
    return is_get_true;
}
void handle_event(void* p_event){
    if(p_event==NULL)return;
    if(((evt*)p_event)->event_type==EVT_1553_RECV_COMMAND||((evt*)(p_event))->event_type==EVT_1553_RECV_COMMAND_ERR){
        handle_1553_func(p_event);
    }
    else if(((evt*)p_event)->event_type==EVT_1553_RETURN_DATA||((evt*)p_event)->event_type==EVT_1553_RETURN_DATA_ERR){
        handle_1553_ret_func(p_event);
    }
    else if(((evt*)p_event)->event_type==EVT_RT_RECV_DATA||((evt*)p_event)->event_type==EVT_RT_RECV_DATA_ERR){
        handle_RT_func(p_event);
    }
    else{
        char* sel_RT_lid_tmp=((evt*)p_event)->sel_RT_lid;
        void* p_route_tmp=get_route_node();
        get_RT_route_map(sel_RT_lid_tmp,&p_route_tmp);
        printf("route:%s %s %s   event_type:%d\n",get_route_bus_type(p_route_tmp),get_route_bus_lid(p_route_tmp),get_route_RT_lid(p_route_tmp),((evt*)p_event)->event_type);
        free_route_node(&p_route_tmp);
    }
    
}
void* get_evt_repos(UINT pos){
    return (void*)p_repos_array[pos];
}
void* evt_repos_scan_pthread_func(void* argc){
    UINT i=0;
    UINT pos=-1;
    for(;i<REPOS_MAX_LEN;i++){
        if(is_repos_avail[i]==0){//已经被注册
            pos=i;
            break;
        }
    }
    if(pos!=-1){
        while(true){
            void* p_repos=get_evt_repos(i);
            void* p_evt_node=(void*)((evt*)malloc(sizeof(evt)));
            bool is_true=get_one_event(p_repos,p_evt_node);
            if(is_true==true){
                handle_event(p_evt_node);
            }
            usleep(500000);
            free(p_evt_node);
        }
    }
}
void create_evt_repos_scan_unit(void){
    pthread_t tid;
    pthread_create(&tid,NULL,evt_repos_scan_pthread_func,NULL);
    printf("成功创建事件库扫描线程...\n");
}
void throw_event(UINT repos_id,char* RT_lid,EVT_TYPE event_type){
    bool is_throw_succeed=false;
    void* p_repos_tmp=get_evt_repos(repos_id);
    if(p_repos_tmp==NULL)return;
    is_throw_succeed=append_event_node(p_repos_tmp,RT_lid,event_type);
    if(is_throw_succeed==false){
        printf("throw event error\n");
    }
}
