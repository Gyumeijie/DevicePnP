#include "../../control_traffic_light.h"
#include "../../config_1553.h"
#include "../../route_map.h"
/*
 *测试交通灯系统仍然需要前几个模块
 */
void print_traffic_light(void* t_node){
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

}
int main(){
    parseXml();
    create_data_trans_rule_form();
    //print_form();
    create_index_list();
    printf("开始测试...\n");
    printf("开始配置1553b总线...\n");
    config_1553();
    printf("配置1553b总线结束...\n");
    printf("开始打印配置信息...\n");
    UINT len=get_config_len();
    UINT num=0;
    printf("配置了%d条总线:\n",len);
    for(;num<len;num++){
        printf("NO%d:\n",num);
        void*p= get_config_node(num);
        printf("bus_lid:%s\n",get_config_node_bus_lid(p));
        printf("traffic_repos_id:%d\n",get_config_node_traffic_repos_id(p));
        printf("RT_num:%d\n",get_config_node_len(p));
        UINT RT_num=get_config_node_len(p);
        UINT i=0;
        printf("port: \n");
        for(;i<RT_num;i++){
            printf("%d ",get_config_node_port(p,i));  
        }
        i=0;
        printf("\nlight_pos: \n");
        for(;i<RT_num;i++){
            printf("%d ",get_config_node_light_pos(p,i));  
        }
        printf("\n");
    }
    printf("打印配置信息结束...\n");
    printf("开始测试交通灯模块...\n");
    UINT con_id=get_1553_bus_config_id("001");
    void* pt= get_config_node(con_id);
    printf("config_id:%d\n",con_id);
    UINT traffic_repos_id=get_config_node_traffic_repos_id(pt);
    void* t_node=get_traffic_repos_node(traffic_repos_id);
    printf("1553 001注册了编号为%d的交通灯库\n",traffic_repos_id);
    printf("开始打印交通灯库内容...\n");
    print_traffic_light(t_node);
    printf("打印交通灯库内容结束...\n");
    printf("测试功能...\n");
    printf("1___\n");
    traffic_repos_scan_func(traffic_repos_id);
    print_traffic_light(t_node);
    UINT scan1=get_scan_pos(traffic_repos_id);
    UINT scan2=get_scan_pos(traffic_repos_id);
    printf("scan1:%d scan2:%d\n",scan1,scan2);
    printf("2___\n");
    set_traffic_light(traffic_repos_id,"001",NOT_SET,LOADED,NOT_SET);
    traffic_repos_scan_func(traffic_repos_id);
    UINT scan3=get_scan_pos(traffic_repos_id);
    printf("scan3:%d\n",scan3);
    print_traffic_light(t_node);
    printf("3___\n");
    traffic_repos_scan_func(traffic_repos_id);
    UINT scan4=get_scan_pos(traffic_repos_id);
    printf("scan4:%d\n",scan4);
    print_traffic_light(t_node);
    printf("4___\n");
    traffic_repos_scan_func(traffic_repos_id);
    UINT scan5=get_scan_pos(traffic_repos_id);
    printf("scan5:%d\n",scan5);
    print_traffic_light(t_node);
    UINT scan6=get_scan_pos(traffic_repos_id);
    printf("scan6:%d\n",scan6);
    printf("5___\n");
    traffic_repos_scan_func(traffic_repos_id);
    print_traffic_light(t_node);
    printf("///////////////\n");
    set_traffic_light(traffic_repos_id,"001",UNCHECKED,NOT_SET,NOT_SET);
    traffic_repos_scan_func(traffic_repos_id);
    print_traffic_light(t_node);
    printf("___\n");
    set_traffic_light(traffic_repos_id,"001",UNCHECKED,NOT_LOADED,BACK);
    traffic_repos_scan_func(traffic_repos_id);
    print_traffic_light(t_node);
    printf("测试交通灯模块结束...\n");
    printf("测试结束...\n");
}
