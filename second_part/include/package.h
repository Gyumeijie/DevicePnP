#ifndef PACKAGE_H_
#define PACKAGE_H_
#include "handle_data_package.h"
#include "control_data_stream.h"
#include "handle_event.h"
#define READ_BUFFER_MAX_SIZE 0x200 //512
#define BUFFER_MAX_SIZE 0x400
#define DATA_BLOCK_INVALID_PREFIX (unsigned char)0x00
#define DATA_BLOCK_VALID_PREFIX (unsigned char)0x80
#define DATA_BLOCK_ISVALID_MASK (unsigned char)0x80
void unpack_package_to_1553(UINT traffic_repos_id,unsigned char* buffer,UINT buf_size,char* bus_type,char* bus_lid,char* RT_lid);
void pack_package_to_1553(UINT traffic_repos_id,UINT light_pos,char* bus_type,char* bus_lid,char* RT_lid,unsigned char* buffer_1553,UINT* buffer_size);
#endif
