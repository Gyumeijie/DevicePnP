#include "RT_control.h"

void clear_write_buffer(){
    int i=0;
    for(;i<MOUNT_DEV_MAX_NUM;i++){
        memset(write_buffer[i],0,CACHE_MAX_SIZE);
    }
}
void write_write_buffer(UINT child_port,unsigned char* buffer,UINT write_size,UINT* size){
    int i=0;
    UINT size_tmp=0;
    int buffer_pos;
    /*for(;i<MOUNT_DEV_MAX_NUM;i++){
        //printf("----%d  %d----\n",child_port_array[i],child_port);
        if(child_port_array[i]==child_port){
            buffer_pos=i;
            break;
        }
    }
    if(buffer_pos==-1){
        *size=0;
        return;
    }*/
    buffer_pos=get_child_port_pos(child_port);
    //printf("port:%d,buffer_pos:%d,buffer:%s\n",child_port,buffer_pos,buffer);
    if(buffer_pos==-1)return;
    UINT write_size_tmp=write_size;
    if(write_size_tmp!=0){
        while(s_pos[buffer_pos]!=(e_pos[buffer_pos]+1)%CACHE_MAX_SIZE){  //空一位
            memcpy(write_buffer[buffer_pos]+e_pos[buffer_pos],buffer+size_tmp,sizeof(char));
            size_tmp++;
            write_size_tmp--;
            e_pos[buffer_pos]=(e_pos[buffer_pos]+1)%CACHE_MAX_SIZE;
            if(write_size_tmp==0)break;
        }
    }
    *size=size_tmp;
}
void read_write_buffer(UINT pos,unsigned char* buffer,UINT read_size,UINT* size){
    UINT size_tmp=0;
    if(pos<0||pos>=len)return;
    while(s_pos[pos]!=e_pos[pos]){
        if(size_tmp==read_size)break;
        memcpy(buffer+size_tmp,write_buffer[pos]+s_pos[pos],sizeof(char));
        size_tmp++;
        s_pos[pos]=(s_pos[pos]+1)%CACHE_MAX_SIZE;
    }
    *size=size_tmp;
}
void init_port_array(UINT RT_physical_addr){
    //根据RT_physical_addr找到RT_lid
    //依次按优先级找到其下的dev_lid,
    //再把每个dev相应的subaddr放到
    //child_port_array中
    printf("正在为地址为%d的RT分配子地址...\n",RT_physical_addr);
    UINT config_1553_id=get_device_num_1553_bus_config_id(BC_device_num);
    if(config_1553_id==-1)return;
    void* p_confgi_node=get_config_node(config_1553_id);
    UINT pos=get_config_light_pos(config_1553_id,RT_physical_addr);
    char* RT_lid=get_config_node_RT_lid(p_confgi_node,pos);
    void* p_route=get_route_node();
    get_RT_route_map(RT_lid,&p_route);
    UINT cur_prio=0;
    UINT prev_priority=MAX_PRIORITY; 
    UINT anchor=0;
    UINT child_port;
    char* dev_lid=get_priority_deterio_dev_lid(get_route_bus_type(p_route),get_route_bus_lid(p_route),get_route_RT_lid(p_route),SEND_PRIORITY_FLAG,prev_priority,&cur_prio,&anchor);
    prev_priority=cur_prio;
    while(strcmp(dev_lid,"")!=0){
        child_port=get_RT_physical_sub_addr(get_route_bus_type(p_route),get_route_bus_lid(p_route),get_route_RT_lid(p_route),dev_lid);
        child_port_array[len++]=child_port;
        dev_lid=get_priority_deterio_dev_lid(get_route_bus_type(p_route),get_route_bus_lid(p_route),get_route_RT_lid(p_route),SEND_PRIORITY_FLAG,prev_priority,&cur_prio,&anchor);
        prev_priority=cur_prio;
    }
    //printf("%d---%d\n",child_port_array[0],child_port_array[1]);
    free_route_node(&p_route);
    printf("完成子地址分配...\n");
}


void pack_package(unsigned char* buffer,UINT* buffer_size){
    //获取数据
    UINT read_size=READ_MAX_SIZE;
    char read_buffer_tmp[CACHE_MAX_SIZE]={0};
    UINT size;
    UINT buffer_pos=0;
    UINT pos=0;
    bool is_send_valid=false;
    //printf("---len:%d\n",len);
    for(;pos<len;pos++){
        read_write_buffer(pos,read_buffer_tmp,read_size,&size);
        //printf("--pos:%d--size:%d--\n",pos,size);
        if(size!=0)is_send_valid=true;
        *(buffer+buffer_pos)=size;
        *(buffer+buffer_pos)|=RT_DATA_BLOCK_VALID_PREFIX;
        buffer_pos++;
        memcpy(buffer+buffer_pos,read_buffer_tmp,size);
        buffer_pos+=size;
        buffer[buffer_pos]='\0';
        memset(read_buffer_tmp,0,CACHE_MAX_SIZE);
    }
    if(is_send_valid==true)*buffer_size=buffer_pos;
    else{
        *buffer_size=0;
        memset(buffer,0,READ_MAX_SIZE);
    }
}
int get_child_port_pos(UINT child_port){
    int pos=-1;
    int i=0;
    for(;i<len;i++){
        if(child_port_array[i]==child_port){
            pos=i;
            break;
        }
    }
    return pos;
}
UINT get_child_port(int pos){
    UINT port_tmp;
    if(pos>=len||pos<0)return 0;
    else port_tmp=child_port_array[pos];
    return port_tmp;
}
UINT get_child_port_array_len(){
    return len;
}
