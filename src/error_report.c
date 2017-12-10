#include "error_report.h"
#include "config_info_collect.h"
#include "driver_match.h"
#include <stdio.h>


void assure_not_null
(
   const char* file_name, 
   const char* func_name,
   const char* para_name, 
   const void* para
)
{
   if (para == NULL){
     fprintf(stderr, "<Error position=\"%s@%s\">\n", func_name, file_name);
     fprintf(stderr, "\t<Message>para named '%s' is null!</Message>\n",
                     para_name);
     fprintf(stderr, "</Error>\n");

     exit(1);
   }
}


void check_malloc(void* mem_addr)
{
   if (mem_addr == NULL){
      fprintf(stderr, "malloc failed!\n");
      exit(1);
   }
}
