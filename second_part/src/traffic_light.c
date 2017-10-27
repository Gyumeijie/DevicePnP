/*
 *定义初始化交通灯结构函数。
 */
#include "traffic_light.h"
void* create_traffic_repos(char* bus_type,char* bus_lid){
    void* p_s_index_list=get_s_index_list(bus_type,bus_lid);
    UINT pos_tmp=0;
    UINT s_index_list_len=get_s_index_list_len(bus_type,bus_lid);
    traffic_light_repos* p_traffic_light_repository=(traffic_light_repos*)malloc(sizeof(traffic_light_repos));

    for(;pos_tmp<s_index_list_len;pos_tmp++){
        void* p_t_index_list=get_t_index_list(bus_type,bus_lid,pos_tmp);
        UINT t_index_list_len=get_t_index_list_len(p_t_index_list);
        int i=0;
        traffic_light* p_traffic_light_list=(traffic_light*)malloc(sizeof(traffic_light)*t_index_list_len);
        for(;i<t_index_list_len;i++){
            char* dev_lid;
            get_t_index_node_lid(p_t_index_list,i,&dev_lid);
            (p_traffic_light_list+i)->dev_lid=dev_lid;
            (p_traffic_light_list+i)->traffic_status=UNCHECKED;
            (p_traffic_light_list+i)->is_loaded=NOT_LOADED;
            (p_traffic_light_list+i)->is_back=NOT_BACK;
            (p_traffic_light_list+i)->count=0;
        }
        char* RT_lid;
        p_traffic_light_repository->p_traffic_light_list[pos_tmp]=p_traffic_light_list;
        p_traffic_light_repository->dev_num[pos_tmp]=t_index_list_len;
        p_traffic_light_repository->is_traffic_enable=TRAFFIC_ENABLE;
        p_traffic_light_repository->RT_section_priority[pos_tmp]=PRIORITY_LOW;
        p_traffic_light_repository->scan_pos=-1;
        get_s_index_node_lid(p_s_index_list,pos_tmp,&RT_lid);
        p_traffic_light_repository->RT_lid_array[pos_tmp]=RT_lid;
        
    }

    p_traffic_light_repository->list_len=s_index_list_len;
    return (void*)p_traffic_light_repository;
}

