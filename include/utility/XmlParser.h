#ifndef XMLPARSER_H
#define XMLPARSER_H

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
#define CONTENT_MAX_LEN 30
typedef struct RTTransaction{
    UINT len;
    char dev_lid[DEV_LID_MAX_LEN][DEV_LID_VALUE_MAX_LEN];
    union info{
        char send_priority[DEV_LID_MAX_LEN][SEND_PRIORITY_VALUE_MAX_LEN];
        char receive_priority[DEV_LID_MAX_LEN][RECEIVE_PRIORITY_VALUE_MAX_LEN];
        char send_block_size[DEV_LID_MAX_LEN][SEND_BLOCK_VALUE_MAX_LEN];
        char receive_block_size[DEV_LID_MAX_LEN][RECEIVE_BLOCK_VALUE_MAX_LEN];
    }info;
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
    RTTransaction RTTrans[TRAN_DATA_ITEM_MAX_LEN];
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
//static IONode* IOList[IO_LIST_MAX_LEN];
static UINT DeviceListLen=0;
static UINT DeviceListPos=0;
static UINT entryPos=0;
static char content[CONTENT_MAX_LEN];
//UINT IOListPos=0;
void parseXml(mxml_node_t* root);
mxml_node_t* findDependedNode(const char* content,UINT content_len,mxml_node_t* root,bool isConfig);
void printList();
char* getInterface(const char* dev_content,UINT dev_content_len);
void* get_devices_descrip_item(void);
UINT get_devices_descrip_item_num(void);
char* get_device_lid(void* descrip);
char* get_device_type(void* descrip);
char* get_device_interface(void* descrip);

#endif
