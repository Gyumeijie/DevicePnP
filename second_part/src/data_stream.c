#include "data_stream.h"
void config_address_map_index_list(void){
    create_index_list();
}
void app_write_data_func(char* dev_lid,unsigned char* buffer,UINT write_size,UINT* size){
    if(write_size>WRITE_MAX_SIZE){
        void* p_route=get_route_node();
        get_dev_route_map(dev_lid,&p_route);
        char* RT_lid=get_route_RT_lid(p_route);
        throw_event(0,RT_lid,EVT_APP_WRITE_BLOCK_OVERFLOW);//报错
        free_route_node(&p_route);
    }
    UINT write_size_tmp=write_size>WRITE_MAX_SIZE?WRITE_MAX_SIZE:write_size;//抛出事件
    void* p_route=get_route_node();
    get_dev_route_map(dev_lid,&p_route);
    void* data_node_array_tmp=get_data_node_array();
    UINT size_tmp;
    plugin_data_node_array(data_node_array_tmp,buffer,write_size,&size_tmp);
    app_write_data(get_route_bus_type(p_route),get_route_bus_lid(p_route),get_route_RT_lid(p_route),dev_lid,data_node_array_tmp,size_tmp,size);
    //设置is_load
    //set_traffic_light(traffic_repos_id,dev_lid,NULL,NULL,LOADED,NULL);
    free_route_node(&p_route);
    free_data_node_array(data_node_array_tmp);
}
void app_read_data_func(char* dev_lid,unsigned char* buffer,UINT read_size,UINT* size,void* time){
    UINT read_size_tmp=read_size>READ_MAX_SIZE?READ_MAX_SIZE:read_size;
    void* p_route=get_route_node();
    get_dev_route_map(dev_lid,&p_route);
    void* data_node_array_tmp=get_data_node_array();
    app_read_data(get_route_bus_type(p_route),get_route_bus_lid(p_route),get_route_RT_lid(p_route),dev_lid,data_node_array_tmp,read_size_tmp,size);
    get_array_data_string(data_node_array_tmp,buffer,*size,size,time);
    //UINT light_pos=get_dev_light_pos(traffic_repos_id,dev_lid);
    //reset_traffic_light
    //reset_traffic_repos_list(traffic_repos_id,light_pos);
    free_route_node(&p_route);
    free_data_node_array(data_node_array_tmp);
}
void dev_write_data_func(char* dev_lid,unsigned char* buffer,UINT write_size,UINT* size){
    if(write_size>WRITE_MAX_SIZE){
        void* p_route=get_route_node();
        get_dev_route_map(dev_lid,&p_route);
        char* RT_lid=get_route_RT_lid(p_route);
        throw_event(0,RT_lid,EVT_1553_RETURN_DATA_ERR);//报错
        free_route_node(&p_route);
    }
    UINT write_size_tmp=write_size>WRITE_MAX_SIZE?WRITE_MAX_SIZE:write_size;//抛出事件
    void* p_route=get_route_node();
    get_dev_route_map(dev_lid,&p_route);
    void* data_node_array_tmp=get_data_node_array();
    UINT size_tmp;
    plugin_data_node_array(data_node_array_tmp,buffer,write_size,&size_tmp);
    dev_write_data(get_route_bus_type(p_route),get_route_bus_lid(p_route),get_route_RT_lid(p_route),dev_lid,data_node_array_tmp,size_tmp,size);
    //set_traffic_light(traffic_repos_id,dev_lid,NULL,NULL,NULL,BACK);
    //设置is_back
    free_route_node(&p_route);
    free_data_node_array(data_node_array_tmp);
}
void dev_read_data_func(char* dev_lid,unsigned char* buffer,UINT read_size,UINT* size,void* time){
    UINT read_size_tmp=read_size>READ_MAX_SIZE?READ_MAX_SIZE:read_size;
    void* p_route=get_route_node();
    get_dev_route_map(dev_lid,&p_route);
    void* data_node_array_tmp=get_data_node_array();
    dev_read_data(get_route_bus_type(p_route),get_route_bus_lid(p_route),get_route_RT_lid(p_route),dev_lid,data_node_array_tmp,read_size_tmp,size);
    get_array_data_string(data_node_array_tmp,buffer,*size,size,time);
    //UINT light_pos=get_dev_light_pos(traffic_repos_id,dev_lid);
    free_route_node(&p_route);
    free_data_node_array(data_node_array_tmp);
}
