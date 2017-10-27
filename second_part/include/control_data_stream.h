/*
 *control_data_stream.h
 */
#ifndef CONTROL_DATA_STREAM_H_
#define CONTROL_DATA_STREAM_H_
#include "data_stream.h"
#include "control_traffic_light.h"
#include "config_1553.h"
#include "handle_event.h"
#define AUTO_SET UINT
#define AUTO 1
#define MANUAL 2
/*
 * 加入信号灯控制
 */
void ctrl_app_write_data(UINT traffic_repos_id,char* dev_lid,unsigned char* buffer,UINT write_size,UINT* size);
/*
 *ctrl_app_read_data每次读取一个block_size,若读不到一个block_size,则放弃读。
 */
void ctrl_app_read_data(UINT traffic_repos_id,char* dev_lid,unsigned char* buffer,UINT read_size,UINT* size,void* time);
void ctrl_dev_write_data(UINT traffic_repos_id,char* dev_lid,unsigned char* buffer,UINT write_size,UINT* size);
void ctrl_dev_read_data(UINT traffic_repos_id,char* dev_lid,unsigned char* buffer,UINT read_size,UINT* size,void* time);
void read_data(char* dev_lid,unsigned char* buffer,UINT buf_size,UINT* size,void* time,AUTO_SET auto_set,UINT set_size);
void write_data(char* dev_lid,unsigned char* buffer,UINT buf_size,UINT* size);
#endif
