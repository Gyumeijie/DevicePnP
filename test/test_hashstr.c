#include<stdio.h>
#include"hashstr.h"

struct hash_item* table[256];

int main()
{
    // 测试基本功能
    char str1[5][40] = {"gyroscope_init_template1","gyroscope_init_template2", "gyroscope_open_template1","gyroscope_close_template1", "gyrosope_getx_template0"};
    int i;

    printf("基本功能测试:\n");
    for (i=0; i<5; i++){
        printf("%s  %d\n", str1[i], add_hash_item(str1[i], i, table, 251));
    }

    for (i=0; i<5; i++){
        printf("%s  %ld\n", str1[i], get_hash_item(str1[i], table, 251)->value);
    }
    printf("\n\n");

    // 测试有相同的键值时
    char str2[5][40] = {"gyroscope_init_template1","gyroscope_init_template1", "gyroscope_open_template1","gyroscope_close_template1", "gyrosope_getx_template0"};

    printf("测试有相同键值时:\n");
    for (i=0; i<5; i++){
        printf("%s  %d\n", str2[i], add_hash_item(str2[i], i, table, 251));
    }

    for (i=0; i<5; i++){
        printf("%s  %ld\n", str2[i], get_hash_item(str2[i], table, 251)->value);
    }
    printf("\n\n");

    //测试键值为NULL时
    printf("测试键值为NULL时:\n");
    printf("%s  %d\n", "null key", add_hash_item(NULL, 0, table, 251));
    printf("\n\n");
    
    //测试hash_table值为NULL时
    printf("测试hash_table为NULL时:\n");
    printf("%s  %d\n", "null key", add_hash_item("gyroscope_init_template1", 0, NULL, 251));
}
