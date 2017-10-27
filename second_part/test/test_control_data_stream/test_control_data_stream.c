#include "../../control_data_stream.h"
void print_traffic_light(void* t_node){
    printf("+++++++++++++++++++++\n");
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
    printf("+++++++++++++++++++++\n");
}
int main(){
    parseXml();
    create_data_trans_rule_form();
    print_form();
    config_address_map_index_list();
    config_1553();
    void* t_node=get_traffic_repos_node(0);
    char app_write_buffer[50]="wang ke wei,ni de jia zai na li?";
    char dev_write_buffer[50]="wo de jia zai hu";
    char dev_write_buffer_err[50]="wo de jia zai hu zhou";
    char read_buffer[50]={0};
    void* time=get_time_node();
    printf("\n\n开始测试app写，dev读\n");
    //traffic_repos_id为0
    UINT size;
    ctrl_app_write_data(0,"001",app_write_buffer,32,&size);
    printf("size:%d\n",size);
    printf("第一次读：\n");
    //ctrl_dev_read_data(0,"001",read_buffer,32,&size,time);
    //print_traffic_light(t_node);
    printf("%d:%d:%d:%d\n",((timeStamp*)time)->day,((timeStamp*)time)->hour,((timeStamp*)time)->minute,((timeStamp*)time)->second);
    
    printf("%s\n",read_buffer);
    
    printf("第二次读：\n");
    memset(read_buffer,0,50);
    //print_traffic_light(t_node);
    traffic_repos_scan_func(0);
    //print_traffic_light(t_node);
    traffic_repos_scan_func(0);
    //traffic_repos_scan_func(0);
    //print_traffic_light(t_node);
    UINT pos=get_scan_pos(0);
    //while(pos==-1){
    //    pos=get_scan_pos(0);
    //};
    printf("scan_pos:%d\n",pos);
    pos=get_scan_pos(0);
    printf("scan_pos:%d\n",pos);
    pos=get_scan_pos(0);
    printf("scan_pos:%d\n",pos);
    ctrl_dev_read_data(0,"001",read_buffer,32,&size,time);
    printf("%d:%d:%d:%d\n",((timeStamp*)time)->day,((timeStamp*)time)->hour,((timeStamp*)time)->minute,((timeStamp*)time)->second);
    printf("%s\n",read_buffer);
    pos=get_scan_pos(0);
    printf("scan_pos:%d\n",pos);
    pos=get_scan_pos(0);
    printf("scan_pos:%d\n",pos);


    printf("第三次读：\n");
    memset(read_buffer,0,50);
    printf("scan_pos:%d\n",pos);
    void* time2=get_time_node();
    ctrl_dev_read_data(0,"001",read_buffer,32,&size,time2);
    printf("%d:%d:%d:%d\n",((timeStamp*)time2)->day,((timeStamp*)time2)->hour,((timeStamp*)time2)->minute,((timeStamp*)time2)->second);
    printf("%s\n",read_buffer);

    printf("\n___开始dev写，app读_____\n");

    memset(read_buffer,0,50);
    ctrl_dev_write_data(0,"001",dev_write_buffer,16,&size);
    ctrl_app_read_data(0,"001",read_buffer,16,&size,time);
    printf("%d:%d:%d:%d\n",((timeStamp*)time)->day,((timeStamp*)time)->hour,((timeStamp*)time)->minute,((timeStamp*)time)->second);
    printf("第一次读:\n");
    printf("%s\n",read_buffer);

    memset(read_buffer,0,50);
    ctrl_dev_write_data(0,"001",dev_write_buffer_err,16,&size);
    read_data("001",read_buffer,50,&size,time,AUTO);
    printf("%d:%d:%d:%d\n",((timeStamp*)time)->day,((timeStamp*)time)->hour,((timeStamp*)time)->minute,((timeStamp*)time)->second);
    printf("第二次读:\n");
    printf("%s\n",read_buffer);
    
    memset(read_buffer,0,50);
    ctrl_dev_write_data(0,"001",dev_write_buffer_err,5,&size);
    read_data("001",read_buffer,50,&size,time,MANUAL);
    printf("%d:%d:%d:%d\n",((timeStamp*)time)->day,((timeStamp*)time)->hour,((timeStamp*)time)->minute,((timeStamp*)time)->second);
    printf("第三次读:\n");
    printf("%s\n",read_buffer);

    printf("_______________\n");
    printf("第一次读:\n");
    memset(read_buffer,0,50);
    write_data("001",app_write_buffer,50,&size);
    ctrl_dev_read_data(0,"001",read_buffer,32,&size,time);
    printf("%d:%d:%d:%d\n",((timeStamp*)time)->day,((timeStamp*)time)->hour,((timeStamp*)time)->minute,((timeStamp*)time)->second);
    printf("%s\n",read_buffer);

    void* time1=get_time_node();
    printf("第二次读:\n");
    memset(read_buffer,0,50);
    write_data("001",app_write_buffer,5,&size);
    ctrl_dev_read_data(0,"001",read_buffer,5,&size,time1);
    printf("%d:%d:%d:%d\n",((timeStamp*)time1)->day,((timeStamp*)time1)->hour,((timeStamp*)time1)->minute,((timeStamp*)time1)->second);
    printf("%s\n",read_buffer);
    
    printf("测试结束\n");
    return 0;
}
