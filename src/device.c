#include "device.h"
#include <malloc.h>
#include <string.h>
#include <stdio.h>


void device_init(void)
{
     device_num = 0;
     memset(device_index_table, 0, sizeof((void*)0)*MAX_DEVICE_TYPE);
     memset(lid2dev_table, 0, sizeof((void*)0)*MAX_DEVICES);
}


/**
 * 输入：设备逻辑标识符指针lid和设备结构体指针devp
 * 输出：无
 * 功能：将设备逻辑标识符与对应的设备结构体建立连接
 * 说明：键值对(logic identifier, device struct pointer)
 */
void lid2dev_mapping(const char* lid, struct device* devp)
{
     long value = (long)devp;
     const void* key = (const void*)lid;

     add_hash_item(key, value, lid2dev_table, PRIME_TABLSIZ);
}


/**
 * 输入：链表头的指针head和链表节点node
 * 输出：无
 * 功能：将给定的链表节点加入到链表的表尾
 */
static void add_device_node(struct device_node** head, struct device_node* node)
{
     if (*head == NULL){
         *head = node;
     }else{
         struct device_node* tmp = *head;
         
         //将该节点加入到链表的表尾
         while (tmp->next != NULL){
               tmp = tmp->next;
         }

         tmp->next = node;
     }
   
}    


/**
 * 输入：设备索引表的索引号index和设备结构体指针devp
 * 输出：无
 * 功能：向设备索引表添加设备
 */
void add_device(int index, struct device* devp)
{
     struct device_node** head = &device_index_table[index];
     struct device_node* node = malloc(sizeof(struct device_node));
     node->devp = devp;
     node->next = NULL;
     
     add_device_node(head, node);
     //设备索引表节点数加１
     device_num++;
}


/**
 * 输入：设备逻辑标识符lid
 * 输出：设备结构体
 * 功能：通过设备逻辑标识符找到对应的设备结构体
 */ 
struct device* find_device(char* lid)
{
    struct device* devp;
    struct hash_item* hip;   

    hip = get_hash_item(lid, lid2dev_table, PRIME_TABLSIZ);
    if (hip == NULL) return NULL;

    devp = (struct device*)hip->value;
    return devp;
}

/**
 * 输入：无
 * 输出：无
 * 功能：每被调用一次，就按序返回设备索引表中的一个设备
 */
struct device* get_device(void)
{
    static struct device_node* node = NULL;
    static int cur_major = -1;
    
    if (cur_major == -1){
        cur_major = get_first_used_major();
        node = device_index_table[cur_major];
    }

    int first_unused_major = get_first_unused_major();
   
    //如果node为NULL，则尝试设备索引表下一个表项对应的链表
    while (node == NULL){
       cur_major++;
       if (cur_major < first_unused_major){
           node = device_index_table[cur_major];
       }else{
           node = NULL;
           cur_major = -1;
           return NULL;
       }
    }
    
    //如果node不为NULL，则在链表内部进行遍历
    struct device* devp = node->devp;
    node = node->next;
    
    return devp;
}


/**
 * 输入：无
 * 输出：无
 * 功能：返回设备索引表中的设备数device_num
 */
unsigned int get_device_num(void)
{
   return device_num;
}
