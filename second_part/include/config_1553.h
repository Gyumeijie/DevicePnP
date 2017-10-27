#ifndef CONFIG_1553_H_
#define CONFIG_1553_H_
#define READ_BUF_1553_MAX_SIZE 10
#define PORT_ARRAY_MAX_SIZE 32
#define RT_LID_ARRAY_MAX_SIZE 32
#define RT_MAX_NUM RT_LID_ARRAY_MAX_SIZE
#define LIGHT_POS_ARRAY_MAX_SIZE 32
#define BUF_MAX_LEN 4096
#include "handle_data_package.h"
#include "control_traffic_light.h"
#include "config_1553.h"
typedef struct config_node{
    char* bus_lid;
    UINT device_num_1553;
    UINT traffic_repos_id;
    UINT len;
    char RT_lid_array[RT_LID_ARRAY_MAX_SIZE][ATTR_LID_VALUE_MAX_LEN];
    UINT port_array[PORT_ARRAY_MAX_SIZE];
    //UINT sub_port_array[PORT_ARRAY_MAX_SIZE];//这里只支持一对一
    UINT light_pos_array[LIGHT_POS_ARRAY_MAX_SIZE];
}config_node;
static config_node* p_config_node_list;
static UINT config_len;
void config_1553(void);
void* get_config_list_entry(void);
void* get_config_node(UINT config_id);
char* get_config_node_bus_lid(void* p_config_node);
UINT  get_config_node_traffic_repos_id(void* p_config_node);
UINT  get_config_node_len(void* p_config_node);
UINT  get_config_node_port(void* p_config_node,UINT pos);
//UINT  get_config_node_sub_port(void* p_config_node,UINT pos);
char* get_config_node_RT_lid(void* p_config_node,UINT pos);
UINT  get_config_node_light_pos(void* p_config_node,UINT pos);
UINT get_config_len(void);
UINT get_1553_bus_config_id(char* bus_lid);
UINT get_device_num_1553_bus_config_id(UINT device_num_1553);
UINT get_config_light_pos(UINT config_id,UINT port);
UINT get_1553_bus_config_id_t(UINT traffic_repos_id);
#endif

