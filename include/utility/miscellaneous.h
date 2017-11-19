#ifndef MISCELLANEOUS_H
#define MISCELLANEOUS_H

#include "types.h"

extern void* convert_type(const char* value, const char* type);

extern Boolean is_equal(const char* str1, const char* str2);

extern void substr(char* dest, const char* src, unsigned int start, 
                   unsigned int cnt);

extern Boolean is_inttype(const char* type);

extern int parse_inttype_for_length(const char* type);

extern int parse_inttype_for_base(const char* type);

static int parse_inttype(const char* type, const char attr);

#define TO_INT(src)  (*((int*)(src)))
#define TO_SHORT_INT(src)  (*((short int*)(src)))
#define TO_CHAR(src)  (*((char*)(src)))
#define TO_FLOAT(src)  (*((float*)(src)))

#if 0
extern void store_data
(
    const void* dest, 
    const void* src, 
    const char* dest_type,
    const char* src_type
);

static void store_floattype_data_from
(
    const char* src_type, 
    const void* dest,
    const void* src
);


static void store_chartype_data_from
(
    const char* src_type, 
    const void* dest,
    const void* src
);


static void store_int16type_data_from
(
    const char* src_type, 
    const void* dest,
    const void* src
);


static void store_int32type_data_from
(
    const char* src_type, 
    const void* dest,
    const void* src
);

#endif
#endif
