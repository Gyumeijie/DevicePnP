#include "manage_transport_center.h"
/*void print_traffic_light(){
    void* t_node=get_traffic_repos_node(0);
    printf("list_len:%d\n",((traffic_light_repos*)t_node)->list_len);
    printf("is_traffic_enable:%d\n",((traffic_light_repos*)t_node)->is_traffic_enable);
    printf("scan_pos:%d\n",((traffic_light_repos*)t_node)->scan_pos);
    UINT i=0;
    traffic_light_repos* p_node=(traffic_light_repos*)t_node;
    for(;i<((traffic_light_repos*)p_node)->list_len;i++){
        traffic_light* l_p=p_node->p_traffic_light_list[i];
        char* RT_lid=p_node->RT_lid_array[i];
        UINT RT_priority=p_node->RT_section_priority[i];
        UINT dev_num=p_node->dev_num[i];
        printf("RT_lid:%s RT_priority:%d dev_num:%d\n",RT_lid,RT_priority,dev_num);
        UINT j=0;
        traffic_light* p_s=p_node->p_traffic_light_list[i];
        for(;j<dev_num;j++){
            traffic_light* p=p_s+j;
            printf("dev_lid:%s status:%d is_loaded:%d is_back:%d count:%d\n",p->dev_lid,p->traffic_status,p->is_loaded,p->is_back,p->count);
        }
   }

}*/
void init_vi_dev_visit_sys(void){
    printf("------开始初始化虚拟设备访问系统------\n");
    usleep(100000);
    parseXml();
    usleep(100000);
    create_data_trans_rule_form();
    usleep(100000);
    config_address_map_index_list();
    usleep(100000);
    init_event_repos_array();
    usleep(100000);
    UINT event_repos_id;
    get_one_event_repos(&event_repos_id);
    //创建事件库扫描线程,事件库一个就够了
    create_evt_repos_scan_unit();
    usleep(100000);
    config_1553();
    usleep(100000);
    //创建交通灯库扫描线程
    create_traffic_repos_scan_unit();
    usleep(100000);
    int i=0;
    UINT len=get_config_len();
    for(;i<len;i++){
       scan_config* p_scan_config_tmp=(scan_config*)malloc(sizeof(scan_config));
       p_scan_config_tmp->config_id=i;
       create_scan_1553_RT_section_unit(p_scan_config_tmp);
       void* p_config_node_tmp=get_config_node(i);
       UINT RT_num=get_config_node_len(p_config_node_tmp);
       UINT j=0;
        //1553模拟器所需的部分
       for(;j<RT_num;j++){
        usleep(100000);
           UINT port_tmp=get_config_node_port(p_config_node_tmp,j);
           //UINT sub_port_tmp=get_config_node_sub_port(p_config_node_tmp,j);
           socket_config* p_socket_config_tmp=(socket_config*)malloc(sizeof(socket_config));
           p_socket_config_tmp->config_id=get_config_node_traffic_repos_id(p_config_node_tmp);
           p_socket_config_tmp->RT_config_id=get_config_node_light_pos(p_config_node_tmp,j);
           p_socket_config_tmp->port=port_tmp;
           //p_socket_config_tmp->sub_port=sub_port_tmp;;
           create_1553_bus_unit(p_socket_config_tmp);
       }
    }
    init_port_array(9000);//测试用
    usleep(100000);
    printf("------初始化虚拟设备访问系统完成------\n");
}
