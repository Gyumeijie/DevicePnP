#include "../../data_stream.h"
int main(){
    parseXml();
    create_data_trans_rule_form();
    print_form();
    config_address_map_index_list();
    printf("开始测试address_map...\n");
    char buffer[100]="wangshaobo";
    char d_buffer[100]="nihao,wangshaobo";
    char read_buffer[100]={0};
    char d_read_buffer[100]={0};
    UINT size_w;
    UINT size_r;
    void* time=get_time_node();
    void* p_route=get_route_node();

    get_dev_route_map("001",&p_route);
    app_write_data_func("001",buffer,10,&size_w);
    printf("应用数据发送:%s\n",buffer);
    printf("size_w:%d\n",size_w);
    printf("bus_type:%s bus_lid:%s RT_lid:%s\n",get_route_bus_type(p_route),get_route_bus_lid(p_route),get_route_RT_lid(p_route));
    printf("size:%d\n",get_read_region_size(get_route_bus_type(p_route),get_route_bus_lid(p_route),get_route_RT_lid(p_route),"001"));
    dev_read_data_func("001",read_buffer,10,&size_r,time);
    printf("size_r:%d\n",size_r);
    printf("%d:%d:%d:%d\n",((timeStamp*)time)->day,((timeStamp*)time)->hour,((timeStamp*)time)->minute,((timeStamp*)time)->second);
    printf("应用数据接收:%s\n",read_buffer);

    get_dev_route_map("002",&p_route);
    dev_write_data_func("002",d_buffer,16,&size_w);
    printf("设备数据发送:%s\n",d_buffer);
    printf("size_w:%d\n",size_w);
    printf("bus_type:%s bus_lid:%s RT_lid:%s\n",get_route_bus_type(p_route),get_route_bus_lid(p_route),get_route_RT_lid(p_route));
    printf("size:%d\n",get_write_region_size(get_route_bus_type(p_route),get_route_bus_lid(p_route),get_route_RT_lid(p_route),"002"));
    printf("size_r:%d\n",size_r);
    app_read_data_func("002",d_read_buffer,16,&size_r,time);
    printf("%d:%d:%d:%d\n",((timeStamp*)time)->day,((timeStamp*)time)->hour,((timeStamp*)time)->minute,((timeStamp*)time)->second);
    printf("设备数据接收:%s\n",d_read_buffer);

    printf("测试address_map结束...\n");
    return 0;
}
