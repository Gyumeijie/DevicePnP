#include "driver.h"
#include "error_report.h"
#include <malloc.h>
#include <string.h>
 
void driver_init(void)
{
   memset(driver_index_table, 0, sizeof((void*)0)*MAX_DEVICE_TYPE);
}


void add_driver_node(struct driver_node** head, struct driver_node* node)
{
   if (*head == NULL){
      *head = node;
    }else{
      struct driver_node* tmp = *head;
        
      // 将该节点加入到链表的表尾
      while (tmp->next != NULL){
         tmp = tmp->next;
      }

         tmp->next = node;
     }
   
}    


int add_driver(int index, struct driver* drip)
{
   struct driver_node** head = &driver_index_table[index];
   struct driver_node* node = malloc(sizeof(struct driver_node));
   check_malloc(node);

   node->drip = drip;
   node->next = NULL;
   add_driver_node(head, node);

   return SUCCESS;
}


struct driver* get_driver(int index, char* device_interface)
{
   struct driver_node* drinodp = driver_index_table[index];

   while (drinodp != NULL){
      struct driver* drip = drinodp->drip;

      if (is_supported_interface(drip->driver_supported_interfaces, 
                                 device_interface))
      {
          return drip;
      }

     drinodp = drinodp->next;
  }

    return NULL;
}


void release_drivers(void)
{
   int i;
   for (i=0; i<MAX_DEVICE_TYPE; i++){
      struct driver_node* drinodp = driver_index_table[i];
      driver_index_table[i] = NULL;

      while (drinodp != NULL){
         struct driver_node* to_be_released = drinodp;
         free(to_be_released);

         drinodp = drinodp->next;
      }
   }
}
