#include "my_dev_socket.h"
void* get_one_dev_port(){
    dev_port_con* p=(dev_port_con*)malloc(sizeof(dev_port_con));
    return (void*)p;
}
void set_dev_port(void* p_port_con,int port){
    dev_port_con* p=(dev_port_con*)p_port_con;
    p->port=port;
}
void* create_dev_socket_server(void* p_port_con){
        dev_port_con* p_port_con_tmp=(dev_port_con*)p_port_con;
        int port=p_port_con_tmp->port;
        int    socket_fd, connect_fd;  
        struct sockaddr_in     servaddr;  
        char    buff[4096];  
        int     n;  
        //初始化Socket  
        if( (socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ){  
        printf("create socket error: %s(errno: %d)\n",strerror(errno),errno);  
        exit(0);  
        }  
        //初始化  
        memset(&servaddr, 0, sizeof(servaddr));  
        servaddr.sin_family = AF_INET;  
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY);//IP地址设置成INADDR_ANY,让系统自动获取本机的IP地址。  
        //servaddr.sin_port = htons(DEFAULT_PORT);//设置的端口为DEFAULT_PORT  
        servaddr.sin_port = htons(port);//
      
        //将本地地址绑定到所创建的套接字上  
        if( bind(socket_fd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1){  
        printf("bind socket error: %s(errno: %d)\n",strerror(errno),errno);  
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
        n = recv(connect_fd, buff,4096, 0);  
    //向客户端发送回应数据  
        buff[n] = '\0';
        if(n!=0){
            printf("端口号为%d的设备接收数据: %s\n",port,buff);  
            if(port==8000){
            if( send(connect_fd,"wo de jia zai chang xin.",24, 0) < 0)  
                {  
                printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);  
                exit(0);  
                }
            }
            if(port==8010){
            if( send(connect_fd,"wo xi huan chi xi gua.",22, 0) < 0)  
                {  
                printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);  
                exit(0);  
                }
            }
        }  
        close(connect_fd);  
        }  
        close(socket_fd);  
    }  
void create_dev_unit(int port){
    void* p=get_one_dev_port();
    set_dev_port(p,port);
    pthread_t t;
    pthread_create(&t,NULL,create_dev_socket_server,p);
    printf("已经启动端口号为:%d的设备...\n",port);
}
