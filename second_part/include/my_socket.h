#ifndef MY_SOCKET_H
#define MY_SOCKET_H
#define MAXLINE 4096
#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#include<errno.h>  
#include<sys/types.h>  
#include<sys/socket.h>  
#include<netinet/in.h>  
#include<unistd.h>
#include "control_package.h"
#include "handle_event.h"
#include "config_1553.h"
#include "RT/my_RT_socket.h"
typedef struct scan_config{
    UINT config_id;
}scan_config;
typedef struct socket_config{
    UINT config_id;
    UINT RT_config_id;
    UINT port;
    UINT sub_port;
}socket_config;
void create_bus_socket_client(UINT config_id,UINT RT_config_id,UINT port);
void create_bus_socket_server(UINT config_id,UINT port);
static unsigned char read_buf_1553[READ_BUF_1553_MAX_SIZE][BUF_MAX_LEN]={0};
static bool is_read_buf_1553_avail[READ_BUF_1553_MAX_SIZE][RT_MAX_NUM]={0};
void* scan_1553_RT_section_pthread_func(void* p_scan_config);
void create_scan_1553_RT_section_unit(void* p_scan_config);
void* bus_socket_pthread_func(void* p_socket_config);
void* bus_ret_socket_pthread_func(void* p_socket_config);
void* RT_socket_pthread_func(void* p_socket_config);
void* RT_ret_socket_pthread_func(void* p_socket_config);
void create_1553_bus_unit(void* p_socket_config);
bool get_buffer_is_avail(UINT config_id,UINT RT_config_id);
bool set_buffer_unavail(UINT config_id,UINT RT_config_id);
bool set_buffer_avail(UINT config_id,UINT RT_config_id);
void get_buffer_content(char* buf,UINT config);
#endif
