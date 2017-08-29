#include "error_report.h"
#include <stdio.h>

void report_error(const char* file, const char* func, const char* msg)
{
#if DEBUG
    printf("<Error position=\"%s@%s\">\n", func, file);
    puts(msg);
    printf("</Error>\n");
#endif
}


int check_null(const char* file, const char* func, const char* para, const void* val)
{
   char msg[1024];

   if (val == NULL){
#if DEBUG
       sprintf(msg, "\t<Message>%s is NULL></Message>", para);
       report_error(file, func, msg);
#endif
       return FAILURE;
   } 

   return SUCCESS;
}

