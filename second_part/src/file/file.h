#ifndef FILE_H_
#define FILE_H_
#include<stdio.h>
#include"relevant_struct_def.h"
#define SEND 1
#define RECEIVE 2
#define STR_MAX_SIZE 0x80000
typedef struct t{
    UINT send_or_rec;
    double data;
    UINT port;
}t;
static UINT is_end=0;
static char out_put_str[STR_MAX_SIZE]={0};
void add_string(UINT send_or_rec,double data,UINT port);
void out_put(void);
void set_is_end(void);
UINT is_end_t(void);
void judge_result(void);
#endif
