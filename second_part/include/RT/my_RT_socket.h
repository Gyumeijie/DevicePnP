#ifndef MY_RT_SOCKET_H_
#define MY_RT_SOCKET_H_
#include "RT_control.h"
#include<pthread.h>
typedef struct port_con{
    UINT port;
}port_con;
void* get_one_port_con();
void create_RT_unit(UINT port,UINT child_port);
void* create_RT_socket_server(void* port_con);
void create_RT_socket_client(char* send_buffer,UINT port);
void* create_RT_ret_socket_client(void* port_con);
void set_RT_port(void* p_port_con,UINT port);
#endif
