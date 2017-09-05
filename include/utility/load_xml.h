#ifndef LOAD_XML_H
#define LOAD_XML_H
#include <mxml.h>

static FILE* fp;

extern mxml_node_t* get_xml_tree(void);

extern void release_xml_tree(void);

#endif
