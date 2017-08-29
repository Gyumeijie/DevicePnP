#ifndef ERROR_REPORT_H
#define ERROR_REPORT_H

#define SUCCESS 1
#define FAILURE 0

extern void report_error(const char* file, const char* func, const char* msg);

extern int check_null(const char* file, const char* func, const char* para, const void* val);

#endif
