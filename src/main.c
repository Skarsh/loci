//
// Created by skarsh on 8/30/24.
//

#include <stdio.h>
#include <stdlib.h>

#include "base/oci_base_core.h"
#include "base/oci_base_memory.h"
#include "base/oci_base_string.h"

typedef struct {
    i32 width;
    i32 height;
} Something;

int main() {
    usize buffer_size = 100;
    void *buffer = malloc(buffer_size);

    oci_Arena arena = {0};
    arena_init(&arena, buffer, buffer_size);

    Something *something = (Something*)arena_alloc(&arena, sizeof(Something));
    something->width = 10;
    something->height = 14;

    printf("Something->width: %d\n", something->width);
    printf("Something->height: %d\n", something->height);

    char *my_char_ptr = "lellele";
    String8 str = str8((u8*)my_char_ptr, strlen(my_char_ptr));

    arena_free_all(&arena);

    return 0;
}
