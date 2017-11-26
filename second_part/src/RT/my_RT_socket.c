#include "my_RT_socket.h"
void* create_RT_socket_server(void* RT_port){
        port_con* p_RT_port=(port_con*)RT_port;
        UINT port=p_RT_port->port;
        //printf("RT server port:%d\n",port);
        UINT child_port;
        int    socket_fd, connect_fd;  
        struct sockaddr_in     servaddr;  
        unsigned char    buffer[4096];  
        unsigned char    ret_buff[4096];
        UINT ret_size;
        int     n;  
        //初始化Socket  
        if( (socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ){  
        printf("create socket error: %s(errno: %d)\n",strerror(errno),errno);  
        exit(0);  
        }  
        //初始化  
        memset(&servaddr, 0, sizeof(servaddr));  
        servaddr.sin_family = AF_INET;  
        servaddr.sin_port = htons(port);//
        //将本地地址绑定到所创建的套接字上  
        if( bind(socket_fd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1){  
        printf("RT--bind socket error: %s(errno: %d)\n",strerror(errno),errno);  
        exit(0);  
        }  
        //开始监听是否有客户端连接  
        if( listen(socket_fd, 10) == -1){  
        printf("listen socket error: %s(errno: %d)\n",strerror(errno),errno);  
        exit(0);  
        }  
        while(1){
    //阻塞直到有客户端连接，不然多浪费CPU资源。  
            if( (connect_fd = accept(socket_fd, (struct sockaddr*)NULL, NULL)) == -1){  
            printf("accept socket error: %s(errno: %d)",strerror(errno),errno);  
            continue;  
        }  
    //接受客户端传过来的数据  
        n = recv(connect_fd, buffer, MAXLINE, 0); 
        buffer[n]='\0';
        //if(n!=0)printf("shoudao:%d--%s\n",n,buffer);
        if(n!=0&&n!=-1){
            //解包
            unsigned char send_buffer[4096]={0};
            UINT size;
            UINT is_valid;
            UINT pos=0;
            UINT port_pos=0;
            while(pos<n){
                size=buffer[pos]%0x80;
                is_valid=buffer[pos]/0x80;
                //printf("va:%d\nsize:%d\n",is_valid,size);
                if(is_valid==0){
                    if(size==0)pos++;
                    else pos+=size;
                    port_pos++;
                    continue;
                }
                if(size==0){
                    pos++;
                    port_pos++;
                    continue;
                }
                pos++;
                memcpy(send_buffer,buffer+pos,size);
                pos+=size;
                //printf("pos:%d\n",pos);
                send_buffer[size]='\0';
                //printf("port_pos:%d,len:%d\n",port_pos,get_child_port_array_len());
                if(port_pos<get_child_port_array_len()){
                    child_port=get_child_port(port_pos);
                    //printf("-----child_port%d\n",child_port);
                    port_pos++;
                }
                else{
                    printf("port_pos大小出错\n");
                }
                //printf("\n----------port为%d的RT捕获到数据：%s发送给child_port:%d端口------------\n",port,send_buffer,child_port);
                double d;
                if(child_port==8003){
                    double d1=send_buffer[0];
                    double d2=send_buffer[1];
                    double d3=send_buffer[2];
                    d=d1+pow(0.1,d3)*d2;
                }
                else {
                    d=send_buffer[0];
                }
                printf("位置：RT；类型：->接收；数据：%lf；大小：%d；端口：%d    ",d,size,child_port);
                add_string(RECEIVE,d,child_port);
                void* p_time=get_time_node();
                get_current_time(p_time);
                print_time(p_time);
                free_time_node(&p_time);
                //create_RT_socket_client(send_buffer,child_port);
                memset(send_buffer,0,4096);
            }
            if(pos!=n){
                printf("ERR:传输内容有误\n");
            }
            
        }
    //向客户端发送回应数据

        close(connect_fd);  
        }  
        close(socket_fd);  

}
void create_RT_socket_client(char* buffer,UINT port){
    int    sockfd, recv_len;
    struct sockaddr_in    servaddr;  
    unsigned char recv_buffer[4096];
    UINT size;
    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){  
    printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);  
    exit(0);  
    }  
    memset(&servaddr, 0, sizeof(servaddr));  
    servaddr.sin_family = AF_INET;  
    servaddr.sin_port = htons(port); 
    //if( inet_pton(AF_INET,"127.0.0.1", &servaddr.sin_addr) <= 0){  
    //exit(0);  
    //}  
    if( connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){  
    printf("connect error: %s(errno: %d)\n",strerror(errno),errno);  
    exit(0);  
    }  
    if( send(sockfd, buffer, strlen(buffer), 0) < 0)  
    {  
    printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);  
    exit(0);  
    }  
    recv_len = recv(sockfd, recv_buffer,4096, 0);
    recv_buffer[recv_len]='\0';
    //printf("---%d---\n",recv_len);
    //printf("recv_len:%d----------------%s\n",recv_len,recv_buffer);
    if(recv_len!=0){
        //write_write_buffer(port,recv_buffer,recv_len,&size);
        //if(size!=recv_len){
        //    printf("ERR:写入RT buffer过程丢失数据\n");
        //}
    }
    close(sockfd);  
    return;
}
void* create_RT_ret_socket_client(void* RT_port){//以原port+1发
    usleep(500000);
    port_con* p_RT_port=(port_con*)RT_port;
    UINT port=p_RT_port->port+1;
    //printf("RT ret client port:%d\n",port);
    int    sockfd, n,rec_len;  
    unsigned char ret_buff[4096]={0};
    UINT ret_size;
    struct sockaddr_in    servaddr;  
    while(1){
    usleep(30000);
    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){  
    printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);  
    exit(0);  
    }  
    memset(&servaddr, 0, sizeof(servaddr));  
    servaddr.sin_family = AF_INET;  
    servaddr.sin_port = htons(port); 
    //if( inet_pton(AF_INET,"127.0.0.1", &servaddr.sin_addr) <= 0){  
    //exit(0);  
    //}  
    if( connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){  
    printf("RT--connect error: %s(errno: %d)\n",strerror(errno),errno);  
    exit(0);  
    }
    pack_package(ret_buff,&ret_size);
    //printf("ret_size:%d\n",ret_size);
    if(ret_size!=0){
        //printf("ret_size:%d 打包发回的数据为:%s\n",ret_size,ret_buff);
        //int s=0;
        //for(;s<ret_size;s++){
        //    printf(" %x ",ret_buff[s]);
        //}
        if(send(sockfd,ret_buff, ret_size,0) == -1)  
            perror("send error");  
            close(sockfd);  
            //exit(0);
    }
    close(sockfd);
    }  
    close(sockfd);  
    exit(0);
}
void set_RT_port(void* p_port_con,UINT port){
    port_con* p_port_con_tmp=(port_con*)p_port_con;
    p_port_con_tmp->port=port;
}
/*void create_RT_unit(UINT port,UINT child_port){
    init_port_array(port);
    set_RT_port(port,child_port);
    pthread_t tid1;
    pthread_create(&tid1,NULL,create_RT_socket_server,(void*)&RT_port);
    char a;
    scanf("y or n:%c",&a);
    if(a=='n')exit(0);
    pthread_t tid2;
    pthread_create(&tid2,NULL,create_RT_ret_socket_client,(void*)&RT_port);
}
*/
void* get_one_port_con(){
    port_con* p=(port_con*)malloc(sizeof(port_con));
    return (void*)p;
}
void* generate_data_1(void* argc){
    unsigned char recv_buffer[5];
    double d=20.005;
    int d1=20;
    int d2=5;
    int d3=3;
    recv_buffer[0]=d1;
    recv_buffer[1]=d2;
    recv_buffer[2]=d3;
    recv_buffer[3]='\0';
    UINT size;
    UINT time;
    UINT t=TIMES;
    while(t--){
        time=m_random();
        usleep(2000*time);
        write_write_buffer(8001,recv_buffer,strlen(recv_buffer),&size);
        if(size!=3)printf("generate data err!\n");
        void* p_time=get_time_node();
        get_current_time(p_time);
        printf("位置：RT，类型：发送；数据：%f；大小：%d；端口：%d    时间戳：%d/%d/%d\n",d,size,8001,((timeStamp*)p_time)->hour,((timeStamp*)p_time)->minute,((timeStamp*)p_time)->second);
        add_string(SEND,d,8001);
        free_time_node(&p_time);
    }
    set_is_end();
}
void* generate_data_2(void* argc){
    unsigned char recv_buffer[5];
    double d=30.01;
    int d1=30;
    int d2=1;
    int d3=2;
    recv_buffer[0]=d1;
    recv_buffer[1]=d2;
    recv_buffer[2]=d3;
    recv_buffer[3]='\0';
    UINT size;
    UINT time;
    UINT t=TIMES;
    while(t--){
        time=m_random();
        usleep(2000*time);
        write_write_buffer(8002,recv_buffer,strlen(recv_buffer),&size);
        if(size!=3)printf("generate data err!\n");
        void* p_time=get_time_node();
        get_current_time(p_time);
        printf("位置：RT，类型：发送；数据：%f；大小：%d；端口：%d    时间戳：%d/%d/%d\n",d,size,8002,((timeStamp*)p_time)->hour,((timeStamp*)p_time)->minute,((timeStamp*)p_time)->second);
        add_string(SEND,d,8002);
        free_time_node(&p_time);
    }
    set_is_end();
}
void* generate_data_4(void* argc){
    unsigned char recv_buffer[5];
    recv_buffer[0]=4;
    recv_buffer[1]='\0';
    UINT size;
    UINT time;
    UINT t=TIMES;
    while(t--){
        time=m_random();
        usleep(2000*time);
        write_write_buffer(8004,recv_buffer,strlen(recv_buffer),&size);
        if(size!=1)printf("generate data err!\n");
        void* p_time=get_time_node();
        get_current_time(p_time);
        printf("位置：RT，类型：发送；数据：%d；大小：%d；端口：%d    时间戳：%d/%d/%d\n",recv_buffer[0],size,8004,((timeStamp*)p_time)->hour,((timeStamp*)p_time)->minute,((timeStamp*)p_time)->second);
        add_string(SEND,recv_buffer[0],8004);
        free_time_node(&p_time);
    }
    set_is_end();
}
void* generate_data_5(void* argc){
    unsigned char recv_buffer[5];
    recv_buffer[0]=5;
    recv_buffer[1]='\0';
    UINT size;
    UINT time;
    UINT t=TIMES;
    while(t--){
        time=m_random();
        usleep(2000*time);
        write_write_buffer(8005,recv_buffer,strlen(recv_buffer),&size);
        if(size!=1)printf("generate data err!\n");
        void* p_time=get_time_node();
        get_current_time(p_time);
        printf("位置：RT，类型：发送；数据：%d；大小：%d；端口：%d    时间戳：%d/%d/%d\n",recv_buffer[0],size,8005,((timeStamp*)p_time)->hour,((timeStamp*)p_time)->minute,((timeStamp*)p_time)->second);
        add_string(SEND,recv_buffer[0],8005);
        free_time_node(&p_time);
    }
    set_is_end();
}
void* generate_data_6(void* argc){
    unsigned char recv_buffer[5];
    recv_buffer[0]=6;
    recv_buffer[1]='\0';
    UINT size;
    UINT time;
    UINT t=TIMES;
    while(t--){
        time=m_random();
        usleep(2000*time);
        write_write_buffer(8006,recv_buffer,strlen(recv_buffer),&size);
        if(size!=1)printf("generate data err!\n");
        void* p_time=get_time_node();
        get_current_time(p_time);
        printf("位置：RT，类型：发送；数据：%d；大小：%d；端口：%d    时间戳：%d/%d/%d\n",recv_buffer[0],size,8006,((timeStamp*)p_time)->hour,((timeStamp*)p_time)->minute,((timeStamp*)p_time)->second);
        add_string(SEND,recv_buffer[0],8006);
        free_time_node(&p_time);
    }
    set_is_end();
}
void* generate_data_7(void* argc){
    unsigned char recv_buffer[5];
    recv_buffer[0]=7;
    recv_buffer[1]='\0';
    UINT size;
    UINT time;
    UINT t=TIMES;
    while(t--){
        time=m_random();
        usleep(2000*time);
        write_write_buffer(8007,recv_buffer,strlen(recv_buffer),&size);
        if(size!=1)printf("generate data err!\n");
        void* p_time=get_time_node();
        get_current_time(p_time);
        printf("位置：RT，类型：发送；数据：%d；大小：%d；端口：%d    时间戳：%d/%d/%d\n",recv_buffer[0],size,8007,((timeStamp*)p_time)->hour,((timeStamp*)p_time)->minute,((timeStamp*)p_time)->second);
        add_string(SEND,recv_buffer[0],8007);
        free_time_node(&p_time);
    }
    set_is_end();
}
void generate_data(void){
    pthread_t tid;
    pthread_create(&tid,NULL,generate_data_1,NULL);
    pthread_create(&tid,NULL,generate_data_2,NULL);
    pthread_create(&tid,NULL,generate_data_4,NULL);
    pthread_create(&tid,NULL,generate_data_5,NULL);
    pthread_create(&tid,NULL,generate_data_6,NULL);
    pthread_create(&tid,NULL,generate_data_7,NULL);
}
