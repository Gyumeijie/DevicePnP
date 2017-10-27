#ifndef ROUTE_MAP_H
#define ROUTE_MAP_H
#include "handle_data_package.h"
typedef struct route{
    char bus_type[ATTR_TYPE_VALUE_MAX_LEN];
    char bus_lid[ATTR_LID_VALUE_MAX_LEN];
    char RT_lid[ATTR_LID_VALUE_MAX_LEN];
}route;
void* get_route_node(void);
char* get_route_bus_type(void* p_route);
char* get_route_bus_lid(void* p_route);
char* get_route_RT_lid(void* p_route);
void get_RT_route_map(char* RT_lid,void** pp_route);
void get_dev_route_map(char* dev_lid,void** pp_route);
void free_route_node(void** pp_route);
#endif
