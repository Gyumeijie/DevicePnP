#include "device.h"
#include "error_report.h"
#include <malloc.h>
#include <string.h>
#include <stdio.h>


void device_init(void)
{
   device_num = 0;
   memset(device_index_table, 0, sizeof((void*)0)*MAX_DEVICE_TYPE);
   memset(lid2dev_table, 0, sizeof((void*)0)*MAX_DEVICES);
}


// 将设备逻辑标识符与对应的设备结构体建立连接，方便后面通过
// 设备设备逻辑号lid查找设备结构体
void lid2dev_mapping(const char* lid, struct device* devp)
{
   long value = (long)devp;
   const void* key = (const void*)lid;

   add_hash_item(key, value, lid2dev_table, PRIME_TABLSIZ);
}


static void add_device_node
(  
   struct device_node** head, 
   struct device_node* node)
{
   if (*head == NULL){
       *head = node;
   }else{
       struct device_node* tmp = *head;
       
       // 将该节点加入到链表的表尾
       while (tmp->next != NULL){
            tmp = tmp->next;
       }

       tmp->next = node;
   }
}    


void add_device(int index, struct device* devp)
{
   struct device_node** head = &device_index_table[index];
   struct device_node* node = malloc(sizeof(struct device_node));
   check_malloc(node);
   node->devp = devp;
   node->next = NULL;
   
   add_device_node(head, node);
   device_num++;
}


struct device* find_device(const char* lid)
{
   struct hash_item* hip = get_hash_item(lid, lid2dev_table, PRIME_TABLSIZ);
   assure_not_null(__FILE__, __func__, "hip", hip); 

   return (struct device*)hip->value;
}


// 每被调用一次，就按序返回设备索引表中的一个设备
struct device* get_device(void)
{
   static struct device_node* node = NULL;
   static int cur_major = -1;
   
   if (cur_major == -1){
       cur_major = get_first_used_major();
        node = device_index_table[cur_major];
   }

   int first_unused_major = get_first_unused_major();
  
   // 如果node为NULL，则尝试设备索引表下一个表项对应的链表
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
    
   // 如果node不为NULL，则在链表内部进行遍历
   struct device* devp = node->devp;
   node = node->next;
    
   return devp;
}


unsigned int get_device_num(void)
{
   return device_num;
}
