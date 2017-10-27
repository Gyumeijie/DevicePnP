/*
 *handle_package.h,声明数据包转发规则表结构和各种对表操作的函数。
 */
#ifndef HANDLE_DATA_PACKAGE_H_
#define HANDLE_DATA_PACKAGE_H_
#include "xml_parse.h"
#include "handle_event.h"
///定义包转发规则表和接口
#define DATA_TRANS_RULE_FORM_MAX_LEN 20
#define RT_TRANS_RULE_MAX_LEN 32
#define DEV_TRANS_DATA_INFO_MAX_LEN 50
#define PRIORITY UINT
#define BLOCK_SIZE UINT
#define TRANS_DEV_MAX_SIZE 100
#define SEND_PRIORITY_FLAG 1
#define SEND_BLOCK_FLAG 2
#define RECEIVE_PRIORITY_FLAG 3
#define RECEIVE_BLOCK_FLAG 4
#define MAX_PRIORITY 1000
#define LOWEST_PRIORITY -1000
#define MIN_DEVIATION 2000
typedef struct dev_trans_data_info{
    char dev_lid[ATTR_LID_VALUE_MAX_LEN];
    UINT data_size;
    char RT_subAddr[RT_SUBADDR_VALUE_MAX_LEN];
    PRIORITY send_priority;
    PRIORITY receive_priority;
    BLOCK_SIZE send_block_size;
    BLOCK_SIZE receive_block_size;
}dev_trans_data_info;
typedef struct RT_trans_rule{
    char RT_lid[ATTR_LID_VALUE_MAX_LEN];
    UINT info_section_len;
    dev_trans_data_info info_section[DEV_TRANS_DATA_INFO_MAX_LEN];
}RT_trans_rule;
typedef struct data_trans_rule_form{
    char bus_lid[ATTR_LID_VALUE_MAX_LEN];
    char bus_type[ATTR_TYPE_VALUE_MAX_LEN];
    UINT rule_section_len;
    RT_trans_rule rule_section[RT_TRANS_RULE_MAX_LEN];
}data_trans_rule_form;
static data_trans_rule_form form[DATA_TRANS_RULE_FORM_MAX_LEN];
static char direct_trans_dev_lid[TRANS_DEV_MAX_SIZE][ATTR_LID_VALUE_MAX_LEN];
static char irdirect_trans_dev_lid[TRANS_DEV_MAX_SIZE][ATTR_LID_VALUE_MAX_LEN];
static char irdirect_trans_bus_type[TRANS_DEV_MAX_SIZE][ATTR_TYPE_VALUE_MAX_LEN];
static char irdirect_trans_bus_lid[TRANS_DEV_MAX_SIZE][ATTR_LID_VALUE_MAX_LEN];
static char irdirect_trans_RT_lid[TRANS_DEV_MAX_SIZE][ATTR_LID_VALUE_MAX_LEN];
static UINT RT_trans_rule_pos=0;
static UINT data_trans_rule_form_num=0;
static UINT direct_trans_dev_num=0;
static UINT irdirect_trans_dev_num=0;
//static UINT priority_deterio_pos=0;
void create_data_trans_rule_form(void);
void print_form();
UINT get_form_num();
void* get_forms_item(UINT item_pos);
char* get_form_bus_lid(void* form_item);
char* get_form_bus_type(void* form_item);
UINT get_form_rule_section_len(void* form_item);
void* get_form_rule_section_item(void* form_item,UINT item_pos);
char* get_form_rule_RT_lid(void* rule_item);
UINT get_form_info_section_len(void* rule_item);
void* get_form_info_section_item(void* rule_item,UINT item_pos);
char* get_form_info_dev_lid(void* info_item);
UINT get_form_info_dev_data_size(void* info_item);
UINT get_form_info_dev_send_priority(void* info_item);
UINT get_form_info_dev_receive_priority(void* info_item);
UINT get_form_info_dev_send_block_size(void* info_item);
UINT get_form_info_dev_receive_block_size(void* info_item);

void* get_form_item(char* bus_type,char* bus_lid);
void* get_form_rule_item(char* bus_type,char* bus_lid,char* RT_lid);
//char* get_max_priority_dev_lid(char* bus_type,char* bus_lid,char* RT_lid,UINT attr_flag,UINT* current_priority,UINT* anchor);
char* get_priority_deterio_dev_lid(char* bus_type,char* bus_lid,char* RT_lid,UINT attr_flag,UINT prev_priority,UINT* current_priority,UINT* anchor);
UINT get_dev_trans_attr(char* bus_type,char* bus_lid,char*RT_lid,char* dev_lid,UINT attr_flag);
UINT get_dev_data_size(char* bus_type,char* bus_lid,char* RT_lid,char* dev_lid);
UINT find_irdirect_dev_pos(char* dev_lid);
UINT find_irdirect_RT_pos(char* RT_lid);
char* get_form_info_dev_RT_subAddr(void* info_item);
char* get_dev_map_RT_subAddr(char* bus_type,char* bus_lid,char*RT_lid,char* dev_lid);
UINT get_1553_device_num(char* bus_type,char* bus_lid);
UINT get_RT_physical_addr(char* bus_type,char* bus_lid,char* RT_lid);
UINT get_RT_physical_sub_addr(char* bus_type,char* bus_lid,char* RT_lid,char* dev_lid);
char* get_irdirect_dev_lid(UINT irdirect_pos);
char* get_irdirect_RT_lid(UINT irdirect_pos);
char* get_irdirect_bus_type(UINT irdirect_pos);
char* get_irdirect_bus_lid(UINT irdirect_pos);
#endif
