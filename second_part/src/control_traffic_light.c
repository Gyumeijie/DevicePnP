/*
 *control_traffic_light.c,定义操作交通灯数据结构的各种操作结构。
 */
#include "control_traffic_light.h"
UINT config_traffic_repos(char* bus_type,char* bus_lid){
    int i=0;
    printf("正在为bus_type:%s,bus_lid:%s的总线创建交通灯库...\n",bus_type,bus_lid);
    for(;i<TRAFFIC_REPOS_ARRAY_MAX_LEN;i++){
        if(p_traffic_light_repos_array[i]==NULL){
            void* p_tmp=create_traffic_repos(bus_type,bus_lid);
            p_traffic_light_repos_array[i]=p_tmp;
            break;
        }
    }
    if(i>=TRAFFIC_REPOS_ARRAY_MAX_LEN||i<0)i=-1;
    return i;
}
void* get_traffic_repos_node(UINT traffic_repos_id){
    return p_traffic_light_repos_array[traffic_repos_id];
}
void config_traffic(){
    UINT form_num=get_form_num();
    int i=0;
    for(;i<form_num;i++){
        void* p_form_item=get_forms_item(i);
        char* bus_type=get_form_bus_type(p_form_item);
        char* bus_lid=get_form_bus_lid(p_form_item);
        config_traffic_repos(bus_type,bus_lid);
    }
}
void* traffic_repos_scan_pthread_func(void* argc){
    int i=0;
    for(;i<TRAFFIC_REPOS_ARRAY_MAX_LEN;i++){
        if(p_traffic_light_repos_array[i]!=NULL){
            while(true){
                traffic_repos_scan_func(i);
                usleep(10000);
            }
        }
    }
}
   
void  set_traffic_light(UINT traffic_repos_id,char* dev_lid,TRAFFIC_STATUS traffic_status,IS_LOADED is_loaded,IS_BACK is_back){
    if(traffic_repos_id<0||traffic_repos_id>=TRAFFIC_REPOS_ARRAY_MAX_LEN||p_traffic_light_repos_array[traffic_repos_id]==NULL)return;  
    traffic_light_repos* p_repos_tmp=(traffic_light_repos*)p_traffic_light_repos_array[traffic_repos_id];
    int i=0;
    for(;i<p_repos_tmp->list_len;i++){
        traffic_light* p_list_tmp=p_repos_tmp->p_traffic_light_list[i];
        int j=0;
        for(;j<p_repos_tmp->dev_num[i];j++){
            traffic_light* p=p_list_tmp+j;
            if(strcmp(p->dev_lid,dev_lid)==0){
                if(traffic_status!=NOT_SET){
                    p_repos_tmp->RT_section_priority[i]=PRIORITY_LOW;
                    if(traffic_status==UNCHECKED){
                        if(p->count==0){
                            void* p_route=get_route_node();
                            get_dev_route_map(dev_lid,&p_route);
                            char* RT_lid=get_route_RT_lid(p_route);
                            throw_event(0,RT_lid,EVT_COUNT_ERR);//报错
                            free_route_node(&p_route);
                        }
                        p->count--;
                    }
                    p->traffic_status=traffic_status;
                }
                if(is_loaded!=NOT_SET){
                    if(is_loaded==LOADED)p->count++;
                    p->is_loaded=is_loaded;
                }
                if(is_back!=NOT_SET)p->is_back=is_back;
            }
        }
    }
}

void traffic_repos_scan_func(UINT traffic_repos_id){
    /*
     * 刷新，20ms间隔
     *若未装载，不予理会
     * 若已经装载，状态为UNCHECK，改状态为GREEN
     * 若已经装载，状态为GREEN，改状态为YELLOW
     * 若已经装载，状态为YELLOW，改状态为RED
     * 若已经装载，状态为RED，不予理会
     * 其它，不予理会
     */
    if(traffic_repos_id<0||traffic_repos_id>=TRAFFIC_REPOS_ARRAY_MAX_LEN||p_traffic_light_repos_array[traffic_repos_id]==NULL)return;
    traffic_light_repos* p_repos_tmp=(traffic_light_repos*)p_traffic_light_repos_array[traffic_repos_id];
    //
        if(p_repos_tmp->is_traffic_enable==TRAFFIC_ENABLE){
            int i=0;
            for(;i<p_repos_tmp->list_len;i++){
                int j=0;
                traffic_light* p_light_tmp=p_repos_tmp->p_traffic_light_list[i];
                for(;j<p_repos_tmp->dev_num[i];j++){
                    p_light_tmp+=j;
                    if(p_light_tmp->is_loaded==NOT_LOADED){
                        //若检测到count不等于零
                        //重置status为GREEN,确保
                        //所有数据都能读出。
                        if(p_light_tmp->count!=0){
                            p_light_tmp->traffic_status==GREEN;
                            p_light_tmp->is_loaded=LOADED;
                        }
                    }
                    if(p_light_tmp->is_loaded==LOADED){
                        if(p_light_tmp->traffic_status==UNCHECKED){
                            p_light_tmp->traffic_status=GREEN;
                        }
                        else if(p_light_tmp->traffic_status==GREEN){
                            p_light_tmp->traffic_status=YELLOW;
                            p_repos_tmp->RT_section_priority[i]=PRIORITY_HIGH;
                        }
                        else if(p_light_tmp->traffic_status==YELLOW){
                            p_light_tmp->traffic_status=RED;
                        }
                    }
                }
            }
        }
    //
}
void set_traffic_repos_disable(UINT traffic_repos_id){
  if(traffic_repos_id<0||traffic_repos_id>=TRAFFIC_REPOS_ARRAY_MAX_LEN||p_traffic_light_repos_array[traffic_repos_id]==NULL)return;
    traffic_light_repos* p_repos_tmp=(traffic_light_repos*)p_traffic_light_repos_array[traffic_repos_id];
    p_repos_tmp->is_traffic_enable=TRAFFIC_DISABLE;
}
void reset_traffic_repos_light(UINT traffic_repos_id,UINT light_pos){
    if(traffic_repos_id<0||traffic_repos_id>=TRAFFIC_REPOS_ARRAY_MAX_LEN||p_traffic_light_repos_array[traffic_repos_id]==NULL)return;
    traffic_light_repos* p_repos_tmp=(traffic_light_repos*)p_traffic_light_repos_array[traffic_repos_id];
    if(light_pos<0||light_pos>=TRAFFIC_LIST_MAX_LEN)return;
    traffic_light* p_light_tmp=p_repos_tmp->p_traffic_light_list[light_pos];
    if(p_light_tmp==NULL)return;

    p_repos_tmp->RT_section_priority[light_pos]=PRIORITY_LOW;
    p_light_tmp->traffic_status=UNCHECKED;
    p_light_tmp->is_loaded=NOT_LOADED;
    p_light_tmp->count=0;
}
UINT get_dev_light_pos(UINT traffic_repos_id,char* dev_lid){
    if(traffic_repos_id<0||traffic_repos_id>=TRAFFIC_REPOS_ARRAY_MAX_LEN||p_traffic_light_repos_array[traffic_repos_id]==NULL)return -1;  
    traffic_light_repos* p_repos_tmp=(traffic_light_repos*)p_traffic_light_repos_array[traffic_repos_id];
    int i=0;
    UINT light_pos=-1;
    for(;i<p_repos_tmp->list_len;i++){
        traffic_light* p_list_tmp=p_repos_tmp->p_traffic_light_list[i];
        int j=0;
        for(;j<p_repos_tmp->dev_num[i];j++){
            traffic_light* p=p_list_tmp+j;
            if(strcmp(p->dev_lid,dev_lid)==0){
                light_pos=i;
                break;
            }
        }
        if(light_pos!=-1)break;
    }
    return light_pos;
}
UINT get_light_pos(UINT traffic_repos_id,char* RT_lid){
    if(traffic_repos_id<0||traffic_repos_id>=TRAFFIC_REPOS_ARRAY_MAX_LEN||p_traffic_light_repos_array[traffic_repos_id]==NULL)return -1;  
    traffic_light_repos* p_repos_tmp=(traffic_light_repos*)p_traffic_light_repos_array[traffic_repos_id]; 
    int i=0;
    UINT light_pos=-1;
    for(;i<p_repos_tmp->list_len;i++){
        char* RT_lid_tmp=p_repos_tmp->RT_lid_array[i];
        if(strcmp(RT_lid,RT_lid_tmp)==0)light_pos=i;
    }
    return light_pos;
}
bool is_RT_section_readable(UINT traffic_repos_id){
    if(traffic_repos_id<0||traffic_repos_id>=TRAFFIC_REPOS_ARRAY_MAX_LEN||p_traffic_light_repos_array[traffic_repos_id]==NULL)return false;
    traffic_light_repos* p_repos_tmp=(traffic_light_repos*)p_traffic_light_repos_array[traffic_repos_id];
    return p_repos_tmp->is_traffic_enable;
}
bool is_RT_section_writeable(UINT traffic_repos_id){        
    if(traffic_repos_id<0||traffic_repos_id>=TRAFFIC_REPOS_ARRAY_MAX_LEN||p_traffic_light_repos_array[traffic_repos_id]==NULL)return false;
    traffic_light_repos* p_repos_tmp=(traffic_light_repos*)p_traffic_light_repos_array[traffic_repos_id];
    return p_repos_tmp->is_traffic_enable;
}
bool is_dev_readable(UINT traffic_repos_id,UINT light_pos,UINT dev_pos){
    if(is_RT_section_readable(traffic_repos_id)==false)return false;
    if(traffic_repos_id<0||traffic_repos_id>=TRAFFIC_REPOS_ARRAY_MAX_LEN||p_traffic_light_repos_array[traffic_repos_id]==NULL)return false;
    traffic_light_repos* p_repos_tmp=(traffic_light_repos*)p_traffic_light_repos_array[traffic_repos_id];
    if(light_pos<0||light_pos>=TRAFFIC_LIST_MAX_LEN)return false;
    traffic_light* p_light_tmp=p_repos_tmp->p_traffic_light_list[light_pos];
    if(p_light_tmp==NULL)return false;
    if((p_light_tmp+dev_pos)->traffic_status==GREEN||(p_light_tmp+dev_pos)->traffic_status==YELLOW||(p_light_tmp+dev_pos)->traffic_status==RED){
        return true;//红灯也要扫描到，读出后丢弃
    }   
    else return false;
}
bool is_red_light(UINT traffic_repos_id,UINT light_pos,char* dev_lid){
    if(traffic_repos_id<0||traffic_repos_id>=TRAFFIC_REPOS_ARRAY_MAX_LEN||p_traffic_light_repos_array[traffic_repos_id]==NULL)return false;
    traffic_light_repos* p_repos_tmp=(traffic_light_repos*)p_traffic_light_repos_array[traffic_repos_id];
    if(light_pos<0||light_pos>=TRAFFIC_LIST_MAX_LEN)return false;
    traffic_light* p_light_tmp=p_repos_tmp->p_traffic_light_list[light_pos];
    if(p_light_tmp==NULL)return false;
    int i=0;
    for(;i<p_repos_tmp->dev_num[light_pos];i++){
        if(strcmp(dev_lid,(p_light_tmp+i)->dev_lid)==0){
            if((p_light_tmp+i)->traffic_status==RED){
                return true;
            }   
        }
    }
    return false;
    
}
UINT get_scan_pos(UINT traffic_repos_id){ 
    UINT next_pos=-1; if(traffic_repos_id<0||traffic_repos_id>=TRAFFIC_REPOS_ARRAY_MAX_LEN||p_traffic_light_repos_array[traffic_repos_id]==NULL)return -1;
    traffic_light_repos* p_repos_tmp=(traffic_light_repos*)p_traffic_light_repos_array[traffic_repos_id];
    UINT pos_tmp=p_repos_tmp->scan_pos;
    int i=pos_tmp==-1?0:pos_tmp;
    UINT list_len_tmp=p_repos_tmp->list_len;
    int j=(i+1)%list_len_tmp;
    UINT count_tmp=list_len_tmp;
    while(count_tmp--){
        UINT light_pos_tmp=j;
        if(p_repos_tmp->RT_section_priority[light_pos_tmp]==PRIORITY_HIGH){
            traffic_light* p_light_tmp=p_repos_tmp->p_traffic_light_list[light_pos_tmp];
            UINT dev_num_tmp=p_repos_tmp->dev_num[light_pos_tmp];
            UINT k=0;
            for(;k<dev_num_tmp;k++){
                if(is_dev_readable(traffic_repos_id,light_pos_tmp,k)){
                    next_pos=light_pos_tmp;
                    break;
                }
            }
        }
        if(next_pos!=-1)break;
        j=(j+1)%list_len_tmp;
    }
    count_tmp=list_len_tmp;
    j=(i+1)%list_len_tmp;
    if(next_pos==-1){
        while(count_tmp--){
            UINT light_pos_tmp=j;
            if(p_repos_tmp->RT_section_priority[light_pos_tmp]==PRIORITY_LOW){
                    traffic_light* p_light_tmp=p_repos_tmp->p_traffic_light_list[light_pos_tmp];
                    UINT dev_num_tmp=p_repos_tmp->dev_num[light_pos_tmp];
                    UINT k=0;
                    for(;k<dev_num_tmp;k++){
                        if(is_dev_readable(traffic_repos_id,light_pos_tmp,k)){
                        next_pos=light_pos_tmp;
                        break;
                    }
                }
            }
        if(next_pos!=-1)break;
        j=(j+1)%list_len_tmp;
        }   
    }
    p_repos_tmp->scan_pos=next_pos;
    return pos_tmp;
}
char* get_RT_section_RT_lid(UINT traffic_repos_id,UINT light_pos){
    char* RT_lid="";
    if(traffic_repos_id<0||traffic_repos_id>=TRAFFIC_REPOS_ARRAY_MAX_LEN||p_traffic_light_repos_array[traffic_repos_id]==NULL)return RT_lid;
    traffic_light_repos* p_repos_tmp=(traffic_light_repos*)p_traffic_light_repos_array[traffic_repos_id];
    if(light_pos<0||light_pos>=TRAFFIC_LIST_MAX_LEN)return RT_lid;
    RT_lid=p_repos_tmp->RT_lid_array[light_pos];
    return RT_lid;
}
void create_traffic_repos_scan_unit(void){
    pthread_t tid;
    int err=pthread_create(&tid,NULL,traffic_repos_scan_pthread_func,NULL);
    if(err!=0)printf("创建交通等库扫描线程失败...\n");
    else printf("成功创建交通灯库扫描线程,本扫描进程每50ms扫描一次所有的交通灯库...\n");
}

