#include "load_xml.h"
#include "error_report.h"


mxml_node_t* get_xml_tree(void)
{
   fp = fopen("device.xml", "r");

   if (!check_null(__FILE__, __func__, "fp", fp)){
       printf("Detail: can't open xml file\n");
       return NULL;
   }

  return mxmlLoadFile(NULL, fp, MXML_NO_CALLBACK);
}

void release_xml_tree(void)
{
    fclose(fp);
}
