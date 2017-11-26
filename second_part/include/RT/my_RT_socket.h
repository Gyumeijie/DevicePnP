#ifndef MY_RT_SOCKET_H_
#define MY_RT_SOCKET_H_
#define m_random() rand()%100
#define TIMES 300
#include "RT_control.h"
#include "file.h"
#include<pthread.h>
#include<stdlib.h> 
#include<pthread.h>
#include<math.h>
typedef struct port_con{
    UINT port;
}port_con;
void* get_one_port_con();
void create_RT_unit(UINT port,UINT child_port);
void* create_RT_socket_server(void* port_con);
void create_RT_socket_client(char* send_buffer,UINT port);
void* create_RT_ret_socket_client(void* port_con);
void set_RT_port(void* p_port_con,UINT port);
void generate_data(void);
void* generate_data_1(void* argc);
void* generate_data_2(void* argc);
void* generate_data_4(void* argc);
void* generate_data_5(void* argc);
void* generate_data_6(void* argc);
void* generate_data_7(void* argc);
#endif
