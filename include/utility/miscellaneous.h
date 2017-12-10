#ifndef MISCELLANEOUS_H
#define MISCELLANEOUS_H

#include "types.h"

extern void* string_to_numeric_value(const char* value, const char* type);

extern Boolean is_equal(const char* str1, const char* str2);

extern Boolean is_not_equal(const char* str1, const char* str2);

extern Boolean is_inttype(const char* type);

extern int parse_inttype_for_length(const char* type);

extern int parse_inttype_for_base(const char* type);

static int parse_inttype(const char* type, const char attr);

#endif
