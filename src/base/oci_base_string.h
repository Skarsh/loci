#ifndef OCI_BASE_STRING_H
#define OCI_BASE_STRING_H

#include "oci_base_core.h"

typedef struct String8 String8;
struct String8 {
    u8 *str;
    u64 size;
};

String8 str8(u8 *str, u64 size);

// Character classification and conversion functions
bool char_is_space(const u8 c);
bool char_is_upper(const u8 c);
bool char_is_lower(u8 c);
bool char_is_alpha(u8 c);
bool char_is_digit(u8 c);
u8 char_to_upper(u8 c);
u8 char_to_lower(u8 c);


#endif //OCI_BASE_STRING_H
