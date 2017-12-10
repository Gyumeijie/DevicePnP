#ifndef HASHSTR_H
#define HASHSTR_H

struct hash_item{
  const char* key;
  long value;
  struct hash_item* next;
};

extern int add_hash_item
(
  const void* key,
  long value,
  struct hash_item* hash_table[], 
  int prime_table_size
);

extern struct hash_item* get_hash_item
(  
   const void* key, 
   struct hash_item* hash_table[], 
   int prime_table_size
);

static unsigned int hashstr
(
   const void* key, 
   int prime_table_size
);

#endif
