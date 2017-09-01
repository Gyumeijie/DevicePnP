#include "driver.h"
#include "error_report.h"
#include <malloc.h>
#include <string.h>
 
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
int add_driver(int index, struct driver* drip)
{
     struct driver_node** head;
     struct driver_node* node;

     head = &driver_index_table[index];
     node = malloc(sizeof(struct driver_node));
     if(!check_null(__FILE__, __func__, "node", node)) return FAILURE;

     node->drip = drip;
     node->next = NULL;
     add_driver_node(head, node);

     return SUCCESS;
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
