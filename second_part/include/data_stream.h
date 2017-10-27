#ifndef DATA_STREAM_H_
#define DATA_STREAM_H_
#include "route_map.h"
#include "address_map.h"
#include "handle_event.h"
#define WRITE_MAX_SIZE WRITE_REGION_MAX_SIZE
#define READ_MAX_SIZE READ_REGION_MAX_SIZE
void config_address_map_index_list(void);
void app_write_data_func(char* dev_lid,unsigned char* buffer,UINT write_size,UINT* size);
void app_read_data_func(char* dev_lid,unsigned char* buffer,UINT read_size,UINT* size,void* time);
void dev_write_data_func(char* dev_lid,unsigned char* buffer,UINT write_size,UINT* size);
void dev_read_data_func(char* dev_lid,unsigned char* buffer,UINT read_size,UINT* size,void* time);
#endif

