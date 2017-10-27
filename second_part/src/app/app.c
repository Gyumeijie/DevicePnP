#include "app.h"
#include<string.h>
#include <unistd.h>
void* app_write_pthread_func(void* argc){
    UINT times=100;
    while(times--){
        char write_buf[200]="wang ke wei,ni de jia zai na li?";
        char write_buf_s[200]="yu mei jie,ni xi huan chi shen me?";
        UINT write_size=0;
        //printf("请输入dev_lid和数据(设备1和设备2都只能接受32个字节数据):\n");
        //scanf("%s%s",dev_lid,write_buf);
        write_data("001",write_buf,200,&write_size);
        printf("\n-------写数据---------\n");
        printf("write_size:%d\n",write_size);
        if(write_size==strlen(write_buf))printf("write success!\ndev_lid:%s   data:%s\n","001",write_buf);
        else printf("write error!\n");
        printf("----------------------\n");
        
        write_data("003",write_buf_s,200,&write_size);
        printf("\n-------写数据---------\n");
        printf("write_size:%d\n",write_size);
        if(write_size==strlen(write_buf_s))printf("write success!\ndev_lid:%s   data:%s\n","003",write_buf_s);
        else printf("write error!\n");
        printf("----------------------\n");
        usleep(5000000);
        
    }
}
void* app_read_pthread_func(void* argc){
    char read_buf[200];
    UINT read_size;
    while(true){
        memset(read_buf,0,200);
        usleep(100000);
        void* p_time_r=get_time_node();
        read_data("001",read_buf,200,&read_size,p_time_r,AUTO,-1);
        //printf("%d:%d:%d\n",((timeStamp*)p_time_r)->hour,((timeStamp*)p_time_r)->minute,((timeStamp*)p_time_r)->second);
        if(read_size!=0){
            printf("\n-------读数据---------\n");
            printf("读到设备%s数据:%s\n","001",read_buf);
            printf("----------------------\n");
        }
        read_data("003",read_buf,200,&read_size,p_time_r,AUTO,-1);
        read_buf[read_size]='\0';
        //printf("%d:%d:%d\n",((timeStamp*)p_time_r)->hour,((timeStamp*)p_time_r)->minute,((timeStamp*)p_time_r)->second);
        free_time_node(&p_time_r);
        if(read_size!=0){
            printf("\n-------读数据---------\n");
            printf("读到设备%s数据:%s\n","003",read_buf);
            printf("----------------------\n");
        }
    }
    
}
