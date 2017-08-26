#include "driver.h"
#include <malloc.h>
#include <string.h>


/**
 * 输入：无
 * 输出：无
 * 功能：初始化driver_index_table
 */ 
void driver_init(void)
{
     // 初始化设备驱动索引表
     memset(driver_index_table, 0, sizeof((void*)0)*MAX_DEVICE_TYPE);
}


/**
 * 输入：链表头的指针head和链表节点node
 * 输出：无
 * 功能：将给定的链表节点加入到链表的表尾
 */
void add_driver_node(struct driver_node** head, struct driver_node* node)
{

     if (*head == NULL){
         *head = node;
     }else{
         struct driver_node* tmp = *head;
         
         //将该节点加入到链表的表尾
         while (tmp->next != NULL){
               tmp = tmp->next;
         }

         tmp->next = node;
     }
   
}    


/**
 * 输入：设备索引表的索引号index和设备驱动结构体指针drip
 * 输出：无
 * 功能：向设备驱动索引表添加设备驱动（驱动注册模块）
 */
void add_driver(int index, struct driver* drip)
{
#if DEBUG
    printf("major: %d interface: %s\n", index, drip->interface);
#endif    
     struct driver_node** head = &driver_index_table[index];
     struct driver_node* node = (struct driver_node*)malloc(sizeof(struct driver_node));
     node->drip = drip;
     node->next = NULL;
     
     add_driver_node(head, node);
}


/**
 *　输入：设备驱动索引表的索引号index以及设备类型interface
 *　输出：设备驱动结构体指针
 *　功能：获取支持给定接口的设备驱动
 */
struct driver* get_driver(int index, interface_t interface)
{
    struct driver_node* drinodp = driver_index_table[index];
    struct driver* drip = NULL;

    //如果没有支持某类型设备的驱动则返回NULL
    if (drinodp == NULL) return NULL;
    while (drinodp != NULL){

        drip = drinodp->drip;
        if (strcmp(drip->interface, interface) == 0){
            return drip;
        }

       drinodp = drinodp->next;
    }

    return NULL;
}
