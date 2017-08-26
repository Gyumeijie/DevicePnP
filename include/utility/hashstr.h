#ifndef HASHSTR_H
#define HASHSTR_H

struct hash_item{
  const char* key;
  long value;
  struct hash_item* next;
};

extern int
add_hash_item(const void* key, long value, struct hash_item* hash_table[], const int prime_tablsiz);

extern struct hash_item* 
get_hash_item(const void* key, struct hash_item* hash_table[], const int prime_tablsiz);

static unsigned int hashstr(const void* key, const int prime_tablsiz);

#endif
