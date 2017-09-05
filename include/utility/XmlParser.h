#ifndef MXML_H
#define MXML_H 
#include<mxml.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define UINT unsigned int
#define ULONG unsigned long
#define ATTR_MAX_LEN 100
#define ATTR_VALUE_MAX_LEN 20
#define ATTR_LID_VALUE_MAX_LEN 30
#define ATTR_TYPE_VALUE_MAX_LEN 30
#define ATTR_INTERFACE_VALUE_MAX_LEN 30
#define DEVICE_LIST_MAX_LEN 200
#define IO_LIST_MAX_LEN 200
#define DEV_LID_MAX_LEN 32
#define DEV_LID_VALUE_MAX_LEN 10
#define SEND_PRIORITY_VALUE_MAX_LEN 10
#define SEND_BLOCK_VALUE_MAX_LEN 10
#define RECEIVE_PRIORITY_VALUE_MAX_LEN 10
#define RECEIVE_BLOCK_VALUE_MAX_LEN 10
#define TRAN_DATA_ITEM_MAX_LEN 5
#define INTERFACE_MAX_LEN 20
#define SEND_PRIORITY_POS 0
#define RECEIVE_PRIORITY_POS 1
#define SEND_BLOCK_POS 2
#define RECEIVE_BLOCK_POS 3
typedef struct RTTransaction{
    UINT len;
    char dev_lid[DEV_LID_MAX_LEN][DEV_LID_VALUE_MAX_LEN];
    union info{
        char send_priority[DEV_LID_MAX_LEN][SEND_PRIORITY_VALUE_MAX_LEN];
        char receive_priority[DEV_LID_MAX_LEN][RECEIVE_PRIORITY_VALUE_MAX_LEN];
        char send_block_size[DEV_LID_MAX_LEN][SEND_BLOCK_VALUE_MAX_LEN];
        char receive_block_size[DEV_LID_MAX_LEN][RECEIVE_BLOCK_VALUE_MAX_LEN];
    }info[TRAN_DATA_ITEM_MAX_LEN];
}RTTransaction;
typedef struct attr{
    char attr_name[ATTR_MAX_LEN][ATTR_VALUE_MAX_LEN];
    char attr_value[ATTR_MAX_LEN][ATTR_VALUE_MAX_LEN];
}attribute;
typedef struct dev_description{
    char lid[ATTR_LID_VALUE_MAX_LEN];
    char type[ATTR_TYPE_VALUE_MAX_LEN];
    char interface[ATTR_INTERFACE_VALUE_MAX_LEN];
    UINT attr_len;
    attribute attrs;
}dev_descrip;
typedef union io_attributes{
    attribute attrs;
    RTTransaction RTTrans;
}io_attributes;
typedef struct io_description{
    char lid[ATTR_LID_VALUE_MAX_LEN];
    char type[ATTR_TYPE_VALUE_MAX_LEN];
    UINT io_attr_len;
    io_attributes io_attrs;
}io_descrip;
typedef struct IONode{
	UINT IO_id;
	io_descrip descrip;
	struct IONode* next;
}IONode;
typedef struct DeviceNode{
	UINT device_id;
	dev_descrip descrip;
	struct IONode* next;
}DeviceNode;
static DeviceNode* DeviceList[DEVICE_LIST_MAX_LEN];
static UINT DeviceListLen=0;
static UINT DeviceListPos=0;
static UINT DescripEntryPos=0;
static UINT dev_attr_name_pos=0;
static UINT dev_attr_value_pos=0;
static UINT io_attr_name_pos=0;
static UINT io_attr_value_pos=0;
static UINT RT_trans_device_lid_pos=0;
static UINT RT_trans_device_s_p_pos=0;
static UINT RT_trans_device_s_b_pos=0;
static UINT RT_trans_device_r_p_pos=0;
static UINT RT_trans_device_r_b_pos=0;
static char interface[INTERFACE_MAX_LEN];
void parseXml(mxml_node_t* root);
char* getInterface(const char* dev_content,UINT dev_content_len);
mxml_node_t* findDependedNode(const char* content,UINT content_len,mxml_node_t* root,bool isConfig);
void printList();
void* get_devices_descrip_item(void);
UINT get_devices_descrip_item_num(void);
char* get_device_lid(void* descrip);
char* get_device_type(void* descrip);
char* get_device_interface(void* descrip);
///
void* get_device_list_items(void);
UINT get_device_attr_len(void* dev_item);
char* get_device_attrs_name(void* dev_item);
char* get_device_attrs_value(void* dev_item);
void* get_device_io_item(void* dev_item);
void* get_io_lid(void* io_item);
char* get_io_type(void* io_item);
UINT get_io_attr_len(void* io_item);//
char* get_io_attrs_name(void* io_tem);
char* get_io_attrs_value(void* io_item);
UINT get_RT_trans_device_num(void* io_item);//
void* get_RT_trans_devices_lid(void* io_item);
char* get_io_attrs_name(void* io_item);
char* get_io_attrs_value(void* io_item);
char* get_RT_trans_devices_send_priority(void* io_item);
char* get_RT_trans_devices_send_block_size(void* io_item);
char* get_RT_trans_devices_receive_priority(void* io_item);
char* get_RT_trans_devices_receive_block_size(void* io_item);
void* get_io_next_item(void* io_item);
#endif

