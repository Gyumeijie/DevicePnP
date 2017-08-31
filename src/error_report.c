#include "error_report.h"
#include "utility/xml_operation.h"
#include "driver_match.h"
#include <stdio.h>

void report_error(const char* file, const char* func, const char* msg)
{
    const char* device_context = get_device_context();
    const char* op_context = get_op_context();

#if DEBUG
    printf("<Error context=\"%s@%s\" position=\"%s@%s\">\n", 
                                      device_context,op_context, func, file);
    printf("\t<Message>%s</Message>\n", msg);
    printf("</Error>\n");
#endif
}


int check_null(const char* file, const char* func, const char* para, const void* val)
{
   char msg[1024];

   if (val == NULL){
#if DEBUG
       sprintf(msg, "'%s' is NULL", para);
       report_error(file, func, msg);
#endif
       return FAILURE;
   } 

   return SUCCESS;
}

