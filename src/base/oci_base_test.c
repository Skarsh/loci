
#include "oci_base_test.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

local_persist Test_Entry *test_list = NULL;

// TODO(Thomas): Use arena or some other allocator instead of malloc here
void test_register(String8 name, Test_Func func) {
    Test_Entry *entry = (Test_Entry*)malloc(sizeof(Test_Entry));
    entry->name = name;
    entry->func = func;
    entry->next = test_list;
    test_list = entry; 
}

void test_run_all(void) {
    u32 total_tests = 0;
    Test_Entry *current = test_list;

    printf("\n=== Running All Tests ===\n");

    while (current != NULL) {
        total_tests++;
        printf("\nExecuting test: %.*s\n", (int)current->name.size, current->name.str);
        current->func();
        current = current->next;
    }

    printf("\n=== All Tests Complete ===\n");
    printf("Total test suites run: %u\n", total_tests);

    while (test_list != NULL) {
        Test_Entry *temp = test_list;
        test_list = test_list->next;
        free(temp);
    }
}

void test_init(Test_Context *ctx, String8 name) {
    ctx->name = name;
    ctx->tests_run = 0;
    ctx->tests_failed = 0;
    ctx->current_test = str8_lit("");
    printf("\n=== Starting Test Suite: %s ===\n", name.str);
}

void test_begin(Test_Context *ctx, String8 test_name) {
    ctx->current_test = test_name;
    ctx->tests_run++;
    printf("\nRunning test: %s\n", test_name.str);
}

void test_assert(Test_Context *ctx, b32 condition, String8 message) {
    if (!condition) {
        ctx->tests_failed++;
        printf("    [FAIL] %s: %s\n", ctx->current_test.str, message.str);
    } else {
        printf("    [PASS]\n");
    }
}

void test_assert_equal_int(Test_Context *ctx, i32 expected, i32 actual, String8 message) {
    if (expected != actual) {
        ctx->tests_failed++;
        printf("    [FAIL] %s: %s\n", ctx->current_test.str, message.str);
        printf("        Expected: %d\n", expected);
        printf("        Got: %d\n", actual);
    } else {
        printf("    [PASS]\n");
    }
}

// TODO(Thomas): Write own strcmp for String8
void test_assert_equal_str(Test_Context *ctx, String8 expected, String8 actual, String8 message) {
    if (expected.size != actual.size && strcmp((char *)expected.str, (char *)actual.str) != 0) {
        printf("    [FAIL] %s: %s\n", ctx->current_test.str, message.str);
        printf("        Expected \"%s\"\n", expected.str);
        printf("        Got \"%s\"\n", actual.str);
    } else {
        printf("    [PASS]\n");
    }
}

void test_assert_equal_mem(Test_Context* ctx, const void* a, const void* b, 
                          usize size, const String8 type_name, const String8 message,
                          b32 expect_equal) {
    b32 are_equal = (memcmp(a, b, size) == 0);
    if (are_equal != expect_equal) {
        ctx->tests_failed++;
        printf("  [FAIL] %.*s: %.*s\n",
               (int)ctx->current_test.size, (char*)ctx->current_test.str,
               (int)message.size, (char*)message.str);
        printf("         Type: %.*s\n", (int)type_name.size, (char*)type_name.str);
        
        if (expect_equal) {
            printf("         Values should be equal but are different\n");
        } else {
            printf("         Values should be different but are equal\n");
        }
        
        // Print hex dump of both structs for debugging
        printf("         First value (%.*s):\n         ", 
               (int)type_name.size, (char*)type_name.str);
        const u8* bytes_a = (const u8*)a;
        const u8* bytes_b = (const u8*)b;
        for (usize i = 0; i < size; i++) {
            printf("%02x ", bytes_a[i]);
            if ((i + 1) % 16 == 0 && i < size - 1) printf("\n         ");
        }
        printf("\n         Second value (%.*s):\n         ",
               (int)type_name.size, (char*)type_name.str);
        for (usize i = 0; i < size; i++) {
            printf("%02x ", bytes_b[i]);
            if ((i + 1) % 16 == 0 && i < size - 1) printf("\n         ");
        }
        printf("\n");
        
        // Mark differing bytes
        printf("         Differences:\n         ");
        for (usize i = 0; i < size; i++) {
            printf("%c  ", (bytes_a[i] != bytes_b[i]) ? 'X' : '.');
            if ((i + 1) % 16 == 0 && i < size - 1) printf("\n         ");
        }
        printf("\n");
    } else {
        printf("  [PASS]");
    }
}
void test_end(Test_Context *ctx) {
    printf("\n=== Test Suite: %s Complete ===\n", ctx->name.str);
    printf("Tests run: %u\n", ctx->tests_run);
    printf("Tests failed: %u\n", ctx->tests_failed);
    printf("Success rate: %.1f%%\n", (ctx->tests_run - ctx->tests_failed) * 100.0f / ctx->tests_run);
}
