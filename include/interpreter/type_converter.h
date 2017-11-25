#ifndef TYPE_CONVERTER_H
#define TYPE_CONVERTER_H

#include "types.h"

extern void numtype_to_strtype(int num_type, char* repr);

extern int strtype_to_numtype(char* type, Boolean is_pointer);

#endif
