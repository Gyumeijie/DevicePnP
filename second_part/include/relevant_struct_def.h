#ifndef RELEVANT_STRUCT_DEF_H_
#define RELEVANT_STRUCT_DEF_H_
#include <time.h>
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unistd.h"
#define UINT unsigned int
#define ULONG unsigned long
#define CACHE_MAX_LEN 0x4000
#define DATA_NODE_ARRY_MAX_LEN 
typedef struct timeStamp{
    UINT year;
    UINT month;
    UINT day;
    UINT hour;
    UINT minute;
    UINT second;
}timeStamp;
typedef struct dataNode{
    timeStamp time;
    //UINT controlCharc;  
    unsigned char dataPiece;
}dataNode;
//static dataNode data_node_array[CACHE_MAX_LEN];
void plugin_data_node_array(void* data_node_array,unsigned char* buf,UINT buf_size,UINT* size);
void* get_data_node_array(void);
void free_data_node_array(void* p_data_node_array);
void get_array_data_string(void* data_node_array,unsigned char* buf,UINT read_size,UINT* size,void* time);
void insert_node_to_data_node_array(void* dest_array,UINT pos,void* src_data_node);
void get_current_time(void* time_stamp);
void clear_data_node_array(void* p_data_node_array,UINT array_size);
void* get_time_node(void);
void free_time_node(void** pp_time_node);
void delay(UINT m_s);
void print_time(void* time_stamp);
#endif
