 /* File Name: server.c */  
#include<stdio.h>  
#include<stdlib.h>  
 #include<string.h>  
#include<errno.h>  
#include<sys/types.h>  
#include<sys/socket.h>  
#include<netinet/in.h>  
#include<unistd.h>
#include<pthread.h>
#define DEFAULT_PORT 8000  
 #define MAXLINE 4096  
typedef struct dev_port_con{
    int port;
}dev_port_con;
void* create_dev_socket_server(void* port_con);
void create_dev_unit(int port);
void set_dev_port(void* p_port_con,int port);
void* get_one_dev_port();
