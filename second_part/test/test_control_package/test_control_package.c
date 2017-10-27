#include "../../control_package.h"
#include "../../control_data_stream.h"
int main(){
    //主要查看打包/解包后的数据对不对,还有get_priority_deterio_dev_lid函数。
    parseXml();
    create_data_trans_rule_form();
    print_form();
    config_address_map_index_list();
    config_1553();
    unsigned char write_buffer_dev1[50]={0};
    unsigned char write_buffer_dev2[50]={0};
    unsigned char buffer[200]={0};
    unsigned char dev_buffer[200]={0};
    unsigned char dev_read_buffer[50]={0};
    UINT dev_size;
    UINT buf_size;
    UINT light_pos;
    UINT read_size;
    int i=0;
    int j=0;
    UINT size1;
    UINT size2;
    printf("\n\n开始测试\n");
    for(;i<32;i++){
        write_buffer_dev1[i]=i;
    }
    for(;j<32;j++){
        write_buffer_dev2[j]=32-j-1;
    }
    write_data("001",write_buffer_dev1,50,&size1);
    if(size1!=32)printf("write dev1 err\n");
    write_data("002",write_buffer_dev2,50,&size2);
    if(size2!=32)printf("write dev2 err\n");
    UINT times=10;
    while(times--){
        memset(buffer,0,200);
        ctrl_pack_package_to_1553(0,buffer,&buf_size,&light_pos);
        if(buf_size!=0){
            printf("buf_size不为零\n");
        }
        UINT k=0;
        for(;k<100;k++){
            if(buffer[k]!=0){
                printf("buffer err\n");
            }
        }
    }
    memset(buffer,0,200);
    traffic_repos_scan_func(0);//默认为零
    ctrl_pack_package_to_1553(0,buffer,&buf_size,&light_pos);
    //第一遍仍旧不能读出
    if(buf_size!=0){
        printf("buf_size不为零\n");
    }
    UINT k=0;
    for(;k<100;k++){
        if(buffer[k]!=0){
            printf("buffer err\n");
        }
    }
    memset(buffer,0,200);
    //应该读出数据
    //UINT s;
    //void* time1=get_time_node();
    //ctrl_dev_read_data(0,"001",buffer,50,&s,time1);
    //printf("s:%d\n",s);
    //memset(buffer,0,50);
    //ctrl_dev_read_data(0,"001",buffer,50,&s,time1);
    //printf("s:%d\n",s);
    ctrl_pack_package_to_1553(0,buffer,&buf_size,&light_pos);
    if(buf_size==0){
        printf("buf_size为零\n");
        printf("light_pos:%d\n",light_pos);
    }
    else {
        printf("buf_size:%d\n",buf_size);
        UINT i=0;
        for(;i<buf_size;i++){
            printf("buffer[%d]:%x\n",i,*(buffer+i));
        }
        strcpy(dev_buffer,buffer);//dev1;
        dev_size=buf_size;
    }
    memset(buffer,0,200);
    //应该读出数据
    ctrl_pack_package_to_1553(0,buffer,&buf_size,&light_pos);
    if(buf_size==0){
        printf("buf_size为零\n");
    }
    else{
        printf("buf_size:%d\n",buf_size);
        UINT i=0;
        for(;i<buf_size;i++){
            printf("buffer[%d]:%x\n",i,*(buffer+i));
        }
    }
    memset(buffer,0,200);
    ctrl_pack_package_to_1553(0,buffer,&buf_size,&light_pos);
    if(buf_size!=0){
        printf("不能再读出数据\n");
        printf("buf_size:%d\n",buf_size);
        UINT i=0;
        for(;i<buf_size;i++){
            printf("buffer[%d]:%x\n",i,*(buffer+i));
        }
    }

    //ctrl_unpack测试
    //dev_buffer[0]=0xa0;
    //i=0;
    //for(;i<32;i++){
    //    dev_buffer[i+1]=i;
    //}
    //dev_size=33;
    void*time=get_time_node();
    //无数据读
    read_data("001",dev_read_buffer,50,&read_size,time,AUTO);
    printf("read_size:%d\n",read_size);
    ctrl_unpack_package_to_1553(0,9000,dev_buffer,dev_size);
    //有数据读
    read_data("001",dev_read_buffer,50,&read_size,time,AUTO);
    if(read_size==0)printf("read_size==0\n");
    else{
        printf("read_size:%d\n",read_size);
        UINT i=0;
        for(;i<read_size;i++){
            printf("dev_read_buffer:%x\n",*(dev_read_buffer+i));
        }
    }
    printf("\n\n测试结束\n");
    return 0;
}
