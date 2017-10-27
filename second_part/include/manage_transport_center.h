#ifndef MANAGE_TRANSPORT_CENTER_H_
#define MANAGE_TRANSPORT_CENTER_H_
#include "control_data_stream.h"
#include "handle_data_package.h"
#include "handle_event.h"
#include "control_package.h"
#include "config_1553.h"
#include "control_traffic_light.h"
#include "bool.h"
#include "relevant_struct_def.h"
#include "my_socket.h"
#include "route_map.h"
#include <pthread.h>
/*
 * 初始化内容：初始化文件解析存储结构，初始化包转发规则表，初始化索引表及转存区域,初始化事件库及扫描线程,
 * 初始化1553配置(包含初始化交通灯库)，创建交通灯库扫描线程，创建所有的1553的RT_section的扫描线程，初始化
 * 所有1553b与RT的socket通信端口。
 */
void init_vi_dev_visit_sys(void); 
#endif
