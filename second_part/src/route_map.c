#include "route_map.h"
void* get_route_node(){
    void* p_route_node=(void*)(route*)malloc(sizeof(route));
    return p_route_node;
}
void get_RT_route_map(char* RT_lid,void** pp_route){
    UINT irdirect_pos=find_irdirect_RT_pos(RT_lid);
    *pp_route=get_route_node();
    strcpy(((route*)(*pp_route))->bus_type,get_irdirect_bus_type(irdirect_pos));
    strcpy(((route*)(*pp_route))->bus_lid,get_irdirect_bus_lid(irdirect_pos));
    strcpy(((route*)(*pp_route))->RT_lid,get_irdirect_RT_lid(irdirect_pos));
}
void get_dev_route_map(char* dev_lid,void** pp_route){
    UINT irdirect_pos=find_irdirect_dev_pos(dev_lid);
    *pp_route=get_route_node();
    strcpy(((route*)(*pp_route))->bus_type,get_irdirect_bus_type(irdirect_pos));
    strcpy(((route*)(*pp_route))->bus_lid,get_irdirect_bus_lid(irdirect_pos));
    strcpy(((route*)(*pp_route))->RT_lid,get_irdirect_RT_lid(irdirect_pos));
}

void free_route_node(void** pp_route){
    route* p_route_tmp=(route*)(*pp_route);
    free(p_route_tmp);
    *pp_route=NULL;
}
char* get_route_bus_type(void* p_route){
    return ((route*)p_route)->bus_type;
}
char* get_route_bus_lid(void* p_route){

    return ((route*)p_route)->bus_lid;
}
char* get_route_RT_lid(void* p_route){
    return ((route*)p_route)->RT_lid;
    
}
