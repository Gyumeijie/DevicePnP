#include "hashstr.h"
#include <malloc.h>
#include <string.h>


/**
 * 输入：键值指针key
 * 输出：槽位号
 * 功能：此函数改编自<<Compilers:Principles, Techniques, and Tools>>
 * 中用到的方法，是P.J.Weinberger为他的编译器所写的一个哈希函数,
 * 这个哈希函针对哈希字符串执行得很好
 */
static unsigned int hashstr(const void* key, const int prime_tablsiz)
{

      const char* ptr;
      unsigned int val;

      val = 0;
      ptr = (const char*)key;
      while (*ptr != '\0'){
               
         unsigned int tmp;
         val = (val << 4) + (*ptr);

         if (tmp = (val & 0xf0000000)){
            
             val = val ^ (tmp >> 24);
             val = val ^ tmp;
         }

         ptr++;
      }


      return val % prime_tablsiz;
}


/**
 *　输入：键值对key和value，哈希表的地址hash_table以及表的大小
 *　输出：如果操作成功则返回槽位号，失败的话返回-1
 *　功能：往hash_table指向的哈希表添加类型为struct hash_item的哈希项
 *  说明：采用开链表法解决冲突
 */
int add_hash_item(const void* key, long value,
                  struct hash_item* hash_table[], const int prime_tablsiz)
{

     unsigned int slot;
     struct hash_item* hip;
     int has_added = 0;
     
     //如果键值或者hash_table为NULL时则返回
     if (key == NULL || hash_table == NULL) return -1;

     hip = (struct hash_item*)malloc(sizeof(struct hash_item));
     if (hip == NULL) return -1;
     hip->key = key;
     hip->value = value;
     hip->next = NULL;

     slot = hashstr(key, prime_tablsiz);
     if (hash_table[slot] == NULL){
         hash_table[slot] = hip;    
     }else{
         struct hash_item* tmp = hash_table[slot];
         struct hash_item* last_item;
         //尝试将该节点加入到链表的表尾
         while (tmp != NULL){
               //已经加入到了链表
               if (strcmp(key, tmp->key) == 0){
                    has_added = 1;
                    break;
               } 

               last_item = tmp; 
               tmp = tmp->next;
         }
        //如果已经加入了链表，则释放hip，否则将其加入到链表
        has_added ? free(hip) : (last_item->next = hip);
         
     }

     return slot;
}


/**
 *　输入：键值对key和value，哈希表的地址hash_table以及表的大小
 *　输出：返回类型为struct hash_item的哈希项或者NULL
 *　功能：根据键key查找相应的哈希项目
 */
struct hash_item*
get_hash_item(const void* key, struct hash_item* hash_table[], const int prime_tablsiz)
{
    unsigned int slot;

    slot = hashstr(key, prime_tablsiz);
    if (hash_table[slot] == NULL){
        return NULL;
    }else{
        struct hash_item* tmp = hash_table[slot];

        while(tmp != NULL){
            if (strcmp(key, tmp->key) == 0){
                return tmp;
            }

            tmp = tmp->next;
        }

        return NULL;
    }
}
