#include "oci_base_memory.h"

#ifndef DEFAULT_ALIGNMENT
#define DEFAULT_ALIGNMENT (2*sizeof(void *))
#endif

// 4 = 100
// 3 = 011
// 4 & 1  => 100 & 011 = 0
internal bool is_power_of_two(uptr x) {
    return (x & (x-1)) == 0;
}

internal uptr align_forward(uptr ptr, usize align) {
    assert(is_power_of_two(align));

    uptr p = ptr;
    const uptr a = (uptr)align;
    // Same as (p % a) but faster as 'a' is a power of two
    const uptr modulo = p & (a - 1);

    if (modulo != 0) {
        // If 'p' address is not aligned, push the address to the
        // next value which is aligned
        p += a - modulo;
    }
    return p;
}

internal void *arena_alloc_align(oci_Arena *arena, usize size, usize align) {
    // Align 'curr_offset' forward to the specified alignment
    uptr curr_ptr = (uptr) arena->buf + (uptr)arena->curr_offset;
    uptr offset = align_forward(curr_ptr, align);
    offset -= (uptr)arena->buf;

    // Check to see if the backing memory has space left
    if (offset + size <= arena->buf_len) {
        void *ptr = &arena->buf[offset];
        arena->prev_offset = offset;
        arena->curr_offset = offset + size;

        // Zero new memory
        memory_zero(ptr, size);
        return ptr;
    }

    // Return NULL if the arena is out of memory (or handle differently)
    return NULL;
}

internal void *arena_resize_align(oci_Arena *arena, void *old_memory, usize old_size, usize new_size, usize align) {
    u8 *old_mem = (u8 *)old_memory;

    assert(is_power_of_two(align));

    if (old_mem == NULL || old_size == 0) {
        return arena_alloc_align(arena, new_size, align);
    } else if (arena->buf <= old_mem && old_mem < arena->buf + arena->buf_len) {
        if (arena->buf + arena->prev_offset == old_mem) {
            arena->curr_offset = arena->prev_offset + new_size;
            if (new_size > old_size) {
                // Zero the new memory by default
                memory_zero(&arena->buf[arena->curr_offset], new_size - old_size);
            }
            return old_memory;
        } else {
            void *new_memory = arena_alloc_align(arena, new_size, align);
            usize copy_size = old_size < new_size ? old_size : new_size;
            // Copy across old memory to new memory
            memory_move(new_memory, old_memory, copy_size);
            return new_memory;
        }
    } else {
        assert(false);
        return NULL;
    }
}

void arena_init(oci_Arena *arena, void *backing_buffer, usize backing_buffer_length) {
    arena->buf = (u8 *)backing_buffer;
    arena->buf_len = backing_buffer_length;
    arena->curr_offset = 0;
    arena->prev_offset = 0;
}

void arena_free_all(oci_Arena *arena) {
    arena->curr_offset = 0;
    arena->prev_offset = 0;
}

void *arena_resize(oci_Arena *arena, void *old_memory, usize old_size, usize new_size) {
    return arena_resize_align(arena, old_memory, old_size, new_size, DEFAULT_ALIGNMENT);
}

void *arena_alloc(oci_Arena *arena, usize size) {
    return arena_alloc_align(arena, size, DEFAULT_ALIGNMENT);
}

