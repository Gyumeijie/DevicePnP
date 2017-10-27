#include "config_1553.h"
void config_1553(){
    printf("注册1553...\n");
    UINT num_1553=get_form_num();
    config_node* p_node=(config_node*)malloc(sizeof(config_node)*num_1553);
    p_config_node_list=p_node;
    int i=0;
    for(;i<num_1553;i++){
        void* p_form_item= get_forms_item(i);
        char* bus_type_tmp=get_form_bus_type(p_form_item);
        if(strcmp(bus_type_tmp,"1553b")!=0)continue;
        char* bus_lid_tmp=get_form_bus_lid(p_form_item);
        UINT device_num_1553_tmp=get_1553_device_num(bus_type_tmp,bus_lid_tmp);
        UINT repos_pos_tmp=config_traffic_repos(bus_type_tmp,bus_lid_tmp);
        (p_node+i)->bus_lid=bus_lid_tmp;
        (p_node+i)->device_num_1553=device_num_1553_tmp;
        (p_node+i)->traffic_repos_id=repos_pos_tmp;
        (p_node+i)->len=0;
        UINT RT_num=get_form_rule_section_len(p_form_item);
        int j=0;
        for(;j<RT_num;j++){
            void* p_RT_item=get_form_rule_section_item(p_form_item,j);
            char* RT_lid_tmp=get_form_rule_RT_lid(p_RT_item);
            UINT port_tmp=get_RT_physical_addr(bus_type_tmp,bus_lid_tmp,RT_lid_tmp);
            //UINT sub_port_tmp=get_RT_physical_sub_addr(bus_type_tmp,bus_lid_tmp,RT_lid_tmp,"");
            UINT light_pos_tmp=get_light_pos(repos_pos_tmp,RT_lid_tmp);
            strcpy((p_node+i)->RT_lid_array[j],RT_lid_tmp);
            //(p_node+i)->sub_port_array[j]=sub_port_tmp;
            (p_node+i)->port_array[j]=port_tmp;
            (p_node+i)->light_pos_array[j]=light_pos_tmp;
            (p_node+i)->len++;
        }
    }
    config_len=num_1553;
    printf("完成注册...\n");
}
UINT get_config_len(){
    return config_len;
}
void* get_config_list_entry(void){
    return (void*)p_config_node_list;
}
UINT get_1553_bus_config_id(char* bus_lid){
    void* entry=get_config_list_entry();
    UINT config_len_tmp=get_config_len();
    int i=0;
    UINT pos_tmp=-1;
    for(;i<config_len_tmp;i++){
        char* bus_lid_tmp=((config_node*)(entry+i))->bus_lid;
        if(strcmp(bus_lid_tmp,bus_lid)==0){
            pos_tmp=i;
            break;
        }
    }
    return pos_tmp;
}
UINT get_1553_bus_config_id_t(UINT traffic_repos_id){
    void* entry=get_config_list_entry();
    UINT config_len_tmp=get_config_len();
    int i=0;
    UINT pos_tmp=-1;
    for(;i<config_len_tmp;i++){
        UINT traffic_repos_id_tmp=((config_node*)(entry+i))->traffic_repos_id;
        if(traffic_repos_id_tmp==traffic_repos_id){
            pos_tmp=i;
            break;
        }
    }
    return pos_tmp;
    
}
UINT get_device_num_1553_bus_config_id(UINT device_num_1553){
    void* entry=get_config_list_entry();
    UINT config_len_tmp=get_config_len();
    int i=0;
    UINT pos_tmp=-1;
    for(;i<config_len_tmp;i++){
        UINT device_num_1553_tmp=((config_node*)(entry+i))->device_num_1553;
        if(device_num_1553_tmp==device_num_1553){
            pos_tmp=i;
            break;
        }
    }
    return pos_tmp;
    
}
void* get_config_node(UINT pos){
    void* p=get_config_list_entry();
    return (void*)((config_node*)p+pos);
}
char* get_config_node_bus_lid(void* p_config_node){
    return ((config_node*)p_config_node)->bus_lid;
}
UINT  get_config_node_traffic_repos_id(void* p_config_node){
    
    return ((config_node*)p_config_node)->traffic_repos_id;
}
UINT  get_config_node_len(void* p_config_node){
    
    return ((config_node*)p_config_node)->len;
}
UINT  get_config_node_port(void* p_config_node,UINT pos){
    
    return ((config_node*)p_config_node)->port_array[pos];
}
//UINT  get_config_node_sub_port(void* p_config_node,UINT pos){
//    return ((config_node*)p_config_node)->sub_port_array[pos];
//}
char* get_config_node_RT_lid(void* p_config_node,UINT pos){
    
    return ((config_node*)p_config_node)->RT_lid_array[pos];
}
UINT  get_config_node_light_pos(void* p_config_node,UINT pos){
    return ((config_node*)p_config_node)->light_pos_array[pos];
}

UINT get_config_light_pos(UINT config_id,UINT port){
    void* p=get_config_node(config_id);
    UINT pos_tmp=-1;
    UINT len_tmp=get_config_node_len(p);
    int i=0;
    for(;i<len_tmp;i++){
        //printf("port:%d\n",get_config_node_port(p,i));
        if(get_config_node_port(p,i)==port){
            pos_tmp=i;
            break;
        }
    }
    if(pos_tmp==-1)return -1;
    return get_config_node_light_pos(p,pos_tmp);
}
