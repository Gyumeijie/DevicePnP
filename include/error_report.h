#ifndef ERROR_REPORT_H
#define ERROR_REPORT_H

//TODO 考虑一些将这些移到types.h中并使用枚举类型
#define SUCCESS 1
#define FAILURE 0

extern void report_error(const char* file, const char* func, const char* msg);

extern int check_null(const char* file, const char* func, const char* para, const void* val);

#endif
