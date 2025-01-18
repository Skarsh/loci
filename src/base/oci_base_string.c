#include "oci_base_string.h"
#include "ctype.h"

String8 str8(u8 *str, const u64 size) {
    return (String8){.str = str, .size = size};
}

// Character classification and conversion functions
bool char_is_space(const u8 c) {
    return (c == ' ' || c == '\n' || c == '\t' || c == '\r' || c == '\f' || c == '\v');
}

bool char_is_upper(const u8 c) {
    return ('A' <= c && c <= 'Z');
}

bool char_is_lower(const u8 c) {
    return ('a' <= c && c <='z');
}

bool char_is_alpha(const u8 c) {
    return (char_is_upper(c) || char_is_lower(c));
}

bool char_is_digit(const u8 c) {
    if isdigit(c) {
        return (true);
    }
    return (false);
}

u8 char_to_upper(u8 c) {
    if (char_is_lower(c)) {
        c += ('A' - 'a');
    }
    return (c);
}

u8 char_to_lower(u8 c) {
    if (char_is_upper(c)) {
        c += ('a' - 'A');
    }
    return (c);
}