#include"hashstr.h"
#include<malloc.h>
#include<string.h>
#include<error_report.h>
#include<miscellaneous.h>


// 此函数改编自<<Compilers:Principles, Techniques, and Tools>>
// 中用到的方法，是P.J.Weinberger为他的编译器所写的一个哈希函数,
// 这个哈希函针对哈希字符串执行得很好
static unsigned int hashstr(const void* key, const int prime_table_size)
{
   unsigned int val = 0;
   const char* ptr = key;
   while (*ptr != '\0'){
            
      unsigned int tmp;
      val = (val << 4) + (*ptr);

      if (tmp = (val & 0xf0000000)){
          val = val ^ (tmp >> 24);
          val = val ^ tmp;
       }

        ptr++;
     }

     return val % prime_table_size;
}


// 采用开链表法解决冲突
int add_hash_item
(
   const void* key,
   long value,
   struct hash_item* hash_table[], 
   int prime_table_size
)
{
   assure_not_null(__FILE__, __func__, "key", key);
   assure_not_null(__FILE__, __func__, "hash_table", hash_table);

   struct hash_item* hip = malloc(sizeof(struct hash_item));
   check_malloc(hip); 

   hip->key = key;
   hip->value = value;
   hip->next = NULL;

   unsigned int slot = hashstr(key, prime_table_size);
   if (hash_table[slot] == NULL){
       hash_table[slot] = hip;    
    } else{

       struct hash_item* tmp = hash_table[slot];
       struct hash_item* last_item;
       int has_added = 0;
       while (tmp != NULL){
           
          //已经加入到了链表
          if (is_equal(key, tmp->key)){
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


struct hash_item* get_hash_item
(  
   const void* key, 
   struct hash_item* hash_table[], 
   int prime_table_size
)
{
   assure_not_null(__FILE__, __func__, "key", key);
   assure_not_null(__FILE__, __func__, "hash_table", hash_table);

   unsigned int slot = hashstr(key, prime_table_size);
   if (hash_table[slot] == NULL){
       return NULL;
   } else{
       struct hash_item* tmp = hash_table[slot];

       while(tmp != NULL){
          if (is_equal(key, tmp->key)){
             return tmp;
          }

          tmp = tmp->next;
       }

        return NULL;
    }
}
