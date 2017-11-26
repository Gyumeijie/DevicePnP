#include "app.h"
#include<string.h>
#include <unistd.h>
#include<math.h>
void* app_write_pthread_func(void* argc){
    UINT times=10;
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
        usleep(1000000);
        
    }
}
void str_to_double(double* data,char* str){
    double d1=str[0];
    double d2=str[1];
    double d3=str[2];
    double d=d1+pow(0.1,d3)*d2;
    *data = d;
}
void* app_read_pthread_func_f(void* argc){
    unsigned char read_buf[200];
    unsigned char write_buf[200];
    UINT read_size;
    UINT write_size;
    double sum;
    double d1;
    double d2;
    //UINT t=1;
    while(true){
        memset(read_buf,0,200);
        void* p_time_r=get_time_node();
        while(true){
            read_data("001",read_buf,200,&read_size,p_time_r,AUTO,-1);
            usleep(10000);
            if(read_size!=0)break;
        }
        str_to_double(&d1,read_buf);
        memset(read_buf,0,200);
        while(true){
            read_data("002",read_buf,200,&read_size,p_time_r,AUTO,-1);
            usleep(10000);
            if(read_size!=0)break;
        }
        str_to_double(&d2,read_buf);
        sum=d1+d2;
        UINT s1=(UINT)sum;
        UINT s2=(UINT)((sum-s1)*1000);
        UINT s3=3; 
        write_buf[0]=s1;
        write_buf[1]=s2;
        write_buf[2]=s3;
        write_buf[3]='\0';
        write_data("003",write_buf,200,&write_size);
        if(write_size==0)printf("写错误\n");
        //printf("位置：APP；类型：发送；数据：%d；大小：%d；端口：%d\n",write_buf[0],write_size,8003);
        //printf("1-%d-\n",t++);
        free_time_node(&p_time_r);
    }
    
}
void* app_read_pthread_func_s(void* argc){
    unsigned char read_buf[200];
    unsigned char write_buf[200];
    UINT read_size;
    UINT write_size;
    UINT sum;
    //UINT t=1;
    while(true){
        memset(read_buf,0,200);
        void* p_time_r=get_time_node();
        while(true){
            read_data("004",read_buf,200,&read_size,p_time_r,AUTO,-1);
            usleep(10000);
            if(read_size!=0)break;
        }
        sum=read_buf[0]+1;
        write_buf[0]=sum;
        write_buf[1]='\0';
        write_data("004",write_buf,200,&write_size);
        if(write_size==0)printf("写错误\n");
        //printf("位置：APP；类型：发送；数据：%d；大小：%d；端口：%d\n",write_buf[0],write_size,8004);
        //printf("2-%d-\n",t++);
        free_time_node(&p_time_r);
    }
    
}
void* app_read_pthread_func_t(void* argc){
    unsigned char read_buf[200];
    unsigned char write_buf[200];
    UINT read_size;
    UINT write_size;
    UINT sum;
    //UINT t=1;
    while(true){
        memset(read_buf,0,200);
        void* p_time_r=get_time_node();
        while(true){
            read_data("005",read_buf,200,&read_size,p_time_r,AUTO,-1);
            usleep(10000);
            if(read_size!=0)break;
        }
        sum=read_buf[0];
        memset(read_buf,0,200);
        while(true){
            read_data("006",read_buf,200,&read_size,p_time_r,AUTO,-1);
            usleep(10000);
            if(read_size!=0)break;
        }
        sum+=read_buf[0];
        memset(read_buf,0,200);
        while(true){
            read_data("007",read_buf,200,&read_size,p_time_r,AUTO,-1);
            usleep(10000);
            if(read_size!=0)break;
        }
        sum+=read_buf[0];
        write_buf[0]=sum;
        write_buf[1]='\0';
        write_data("007",write_buf,200,&write_size);
        if(write_size==0)printf("写错误\n");
        write_data("008",write_buf,200,&write_size);
        if(write_size==0)printf("写错误\n");
        //printf("位置：APP；类型：发送；数据：%d；大小：%d；端口：%d\n",write_buf[0],write_size,8007);
        //printf("位置：APP；类型：发送；数据：%d；大小：%d；端口：%d\n",write_buf[0],write_size,8008);
        //printf("3-%d-\n",t++);
        free_time_node(&p_time_r);
    }
    
}
void app_read(void){
    pthread_t tid1;
    pthread_create(&tid1,NULL,app_read_pthread_func_f,NULL);
    pthread_t tid2;
    pthread_create(&tid2,NULL,app_read_pthread_func_s,NULL);
    pthread_t tid3;
    pthread_create(&tid3,NULL,app_read_pthread_func_t,NULL);
}
