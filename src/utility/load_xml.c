#include "load_xml.h"
#include "error_report.h"
#include "xml_configuration.h"

static mxml_node_t* tree;
mxml_node_t* get_xml_tree(void)
{
   if (tree == NULL) {
      return  mxmlLoadString(NULL, config_str, MXML_TEXT_CALLBACK);
   } else {
      return tree; 
   }
}

void release_xml_tree(void) { }
