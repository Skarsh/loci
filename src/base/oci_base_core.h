#ifndef OCI_BASE_CORE_H
#define OCI_BASE_CORE_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

// -------- Context cracking -------- //

#if defined(__x86_64__) || defined(_M_AMD64) || defined(_M_X64)
#define ARCH_X64 1
#elif defined(__i386__)
#define ARCH_x86 1
#elif defined(__arm__)
#define ARCH_ARM32 1
#elif defined(__aarch64__)
#define ARCH_ARM64 1
#else
#error "Unsupported architecture"
#endif

#if defined(_WIN32)
#define OS_WINDOWS 1
#elif defined(__gnu_linux__)
#define OS_LINUX 1
#elif defined(__APPLE__) && defined(__MACH__)
#define OS_MAC 1
#else
#error "Unsupported OS"
#endif

// Compiler matching
#if defined(__clang__)
#define COMPILER_CLANG 1
#endif
#if defined(_MSC_VER)
#define COMPILER_CL 1
#endif
#if defined(__GNUC__)
#define COMPILER_GCC 1
#endif

// Zero fill missing context macros

#if !defined(ARCH_X64)
#define ARCH_X64 0
#endif
#if !defined(__i386__)
#define ARCH_x86 0
#endif
#if !defined(__arm__)
#define ARCH_ARM32 0
#endif
#if !defined(__aarch64__)
#define ARCH_ARM64 0
#endif

#if !defined(OS_WINDOWS)
#define OS_WINDOWS 0
#endif
#if !defined(OS_LINUX)
#define OS_LINUX 0
#endif
#if !defined(OS_MAC)
#define OS_MAC 0
#endif

#if !defined(COMPILER_CLANG)
#define COMPILER_CLANG 0
#endif
#if !defined(COMPILER_CL)
#define COMPILER_CL 0
#endif
#if !defined(COMPILER_GCC)
#define COMPILER_GCC 0
#endif


// -------- Macros -------- //
// TODO(Thomas): Complete assertion macro
#define assert(expression) if(!(expression)) {*(volatile int *)0 = 0;}
#define memory_copy memcpy
#define memory_move memmove
#define memory_set memset

#define memory_zero(ptr, size) memory_set((ptr), 0, (size))
#define memory_zero_struct(ptr) memory_zero((ptr), sizeof(*ptr)))
#define memory_zero_array(arr) memory_zero((arr), sizeof(arr))

#define array_count(a) (sizeof(a) / sizeof(a)[0])

// -------- Types -------- //
#define internal static
#define local_persist static
#define global_variable static

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef i32 b32;

typedef float f32;
typedef double f64;

typedef size_t usize;

typedef intptr_t iptr;
typedef uintptr_t uptr;

// -------- Constants -------- //
#define Pi32 3.14159265259f

#endif //OCI_BASE_CORE_H
