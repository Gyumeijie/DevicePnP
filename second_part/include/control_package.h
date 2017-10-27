#ifndef CONTROL_PACKAGE_H_
#define CONTROL_PACKAGE_H_
#include "package.h"
#include "control_traffic_light.h"
#include "handle_event.h"
#include "config_1553.h"
#include "route_map.h"
void ctrl_unpack_package_to_1553(UINT traffic_repos_id,UINT port,unsigned char* buffer,UINT buf_size);
void ctrl_pack_package_to_1553(UINT traffic_repos_id,unsigned char* buffer_1553,UINT* buf_size,UINT* light_pos);
#endif
