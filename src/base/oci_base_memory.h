#ifndef OCI_BASE_MEMORY_H
#define OCI_BASE_MEMORY_H

#include "oci_base_core.h"

typedef struct oci_Arena oci_Arena;
struct oci_Arena {
    u8 *buf;
    usize buf_len;
    usize prev_offset;
    usize curr_offset;
};

void arena_init(oci_Arena *arena, void *backing_buffer, usize backing_buffer_length);

void arena_free(oci_Arena *arena, void *ptr);

void arena_free_all(oci_Arena *arena);

void *arena_alloc(oci_Arena *arena, usize size);

void *arena_resize(oci_Arena *arena, void *old_memory, usize old_size, usize new_size);

#endif //OCI_BASE_MEMORY_H
