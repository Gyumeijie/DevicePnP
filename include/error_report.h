#ifndef ERROR_REPORT_H
#define ERROR_REPORT_H

//TODO 考虑一些将这些移到types.h中并使用枚举类型
#define SUCCESS 1
#define FAILURE 0

extern void assure_not_null
(
   const char* file_name, 
   const char* func_name,
   const char* para_name, 
   const void* para
);

extern void check_malloc(void* mem_addr);


#endif
