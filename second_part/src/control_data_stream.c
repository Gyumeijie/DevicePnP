/*
 *control_data_stream.c
 */
#include "control_data_stream.h"
void ctrl_app_write_data(UINT traffic_repos_id,char* dev_lid,unsigned char* buffer,UINT write_size,UINT* size){
    app_write_data_func(dev_lid,buffer,write_size,size);
    if(*size==0)return;
    UINT size_tmp=*size;
    while(write_size-size_tmp){
        app_write_data_func(dev_lid,buffer+size_tmp,write_size-size_tmp,size);
        size_tmp+=*size;
    }
    *size=size_tmp;
    //is_load
    set_traffic_light(traffic_repos_id,dev_lid,NOT_SET,LOADED,NOT_SET);
}
void ctrl_app_read_data(UINT traffic_repos_id,char* dev_lid,unsigned char* buffer,UINT read_size,UINT* size,void* time){
    app_read_data_func(dev_lid,buffer,read_size,size,time);
    if(*size==0)return;
    void* p_route=get_route_node();
    get_dev_route_map(dev_lid,&p_route);
    if(is_write_region_empty(get_route_bus_type(p_route),get_route_bus_lid(p_route),get_route_RT_lid(p_route),dev_lid)){
        set_traffic_light(traffic_repos_id,dev_lid,NOT_SET,NOT_SET,NOT_BACK);
    }
    free_route_node(&p_route);
}
void ctrl_dev_write_data(UINT traffic_repos_id,char* dev_lid,unsigned char* buffer,UINT write_size,UINT* size){
    //printf("---dev_lid:%s\n",dev_lid);
    dev_write_data_func(dev_lid,buffer,write_size,size);
    if(*size==0)return;
    UINT size_tmp=*size;
    while(write_size-size_tmp){
        dev_write_data_func(dev_lid,buffer+size_tmp,write_size-size_tmp,size);
        size_tmp+=*size;
    }
    *size=size_tmp;
    //is_load
    set_traffic_light(traffic_repos_id,dev_lid,NOT_SET,NOT_SET,BACK);
}
void ctrl_dev_read_data(UINT traffic_repos_id,char* dev_lid,unsigned char* buffer,UINT read_size,UINT* size,void* time){
    UINT light_pos=get_dev_light_pos(traffic_repos_id,dev_lid);
    void* p_route=get_route_node();
    get_dev_route_map(dev_lid,&p_route);
    if(is_red_light(traffic_repos_id,light_pos,dev_lid)){
        dev_read_data_func(dev_lid,buffer,read_size,size,time);//红灯读出丢弃数据,抛出事件
        memset(buffer,0,read_size);
        if(*size==0){
            //抛出事件
            char* RT_lid=get_route_RT_lid(p_route);
            throw_event(0,RT_lid,EVT_1553_RECV_COMMAND_ERR);
            return;
        }
        if(is_read_region_empty(get_route_bus_type(p_route),get_route_bus_lid(p_route),get_route_RT_lid(p_route),dev_lid)){
            set_traffic_light(traffic_repos_id,dev_lid,UNCHECKED,NOT_LOADED,NOT_SET);
        }
        else set_traffic_light(traffic_repos_id,dev_lid,UNCHECKED,NOT_SET,NOT_SET);
        *size=0;
        return;
    }
    dev_read_data_func(dev_lid,buffer,read_size,size,time);
    if(*size==0){return;}
    if(is_read_region_empty(get_route_bus_type(p_route),get_route_bus_lid(p_route),get_route_RT_lid(p_route),dev_lid)){
        set_traffic_light(traffic_repos_id,dev_lid,UNCHECKED,NOT_LOADED,NOT_SET);
    }
    else set_traffic_light(traffic_repos_id,dev_lid,UNCHECKED,NOT_SET,NOT_SET);
    free_route_node(&p_route);
}
//读写都为读写block_size
void read_data(char* dev_lid,unsigned char* buffer,UINT buffer_size,UINT* size,void* time,AUTO_SET auto_set,UINT set_size){
    void* p_route_tmp=get_route_node();
    get_dev_route_map(dev_lid,&p_route_tmp);
    char* bus_type=((route*)p_route_tmp)->bus_type;
    char* bus_lid=((route*)p_route_tmp)->bus_lid;
    char* RT_lid=((route*)p_route_tmp)->RT_lid;
    UINT read_block_size=get_dev_trans_attr(bus_type,bus_lid,RT_lid,dev_lid,SEND_BLOCK_FLAG);
    if(read_block_size>buffer_size){
        *size=0;
        throw_event(0,RT_lid,EVT_APP_READ_BLOCK_OVERFLOW);
        return;//抛出事件
    }
    if(auto_set==AUTO){
        //printf("region size:%d\n",get_write_region_size(bus_type,bus_lid,RT_lid,dev_lid));
        if(get_write_region_size(bus_type,bus_lid,RT_lid,dev_lid)<read_block_size){
            *size=0;
            return;
        }
    }
    else{
        if(set_size>0){
            read_block_size=set_size;
        }
    }
    UINT config_id=get_1553_bus_config_id(bus_lid);
    void* p_config_node=get_config_node(config_id);
    UINT traffic_repos_id=get_config_node_traffic_repos_id(p_config_node);
    ctrl_app_read_data(traffic_repos_id,dev_lid,buffer,read_block_size,size,time);
    free_route_node(&p_route_tmp);
}
void write_data(char* dev_lid,unsigned char* buffer,UINT buffer_size,UINT* size){
    void* p_route_tmp=get_route_node();
    get_dev_route_map(dev_lid,&p_route_tmp);
    char* bus_type=((route*)p_route_tmp)->bus_type;
    char* bus_lid=((route*)p_route_tmp)->bus_lid;
    char* RT_lid=((route*)p_route_tmp)->RT_lid;
    UINT send_block_size=get_dev_trans_attr(bus_type,bus_lid,RT_lid,dev_lid,RECEIVE_BLOCK_FLAG);
    if(send_block_size>buffer_size){
        *size=0;
        throw_event(0,RT_lid,EVT_APP_WRITE_BLOCK_OVERFLOW);
        return;//抛出事件
    }
    if(send_block_size!=strlen(buffer)){
        *size=0;
        return;
    }
    UINT config_id=get_1553_bus_config_id(bus_lid);
    void* p_config_node=get_config_node(config_id);
    UINT traffic_repos_id=get_config_node_traffic_repos_id(p_config_node);
    ctrl_app_write_data(traffic_repos_id,dev_lid,buffer,send_block_size,size);
    free_route_node(&p_route_tmp);

}
