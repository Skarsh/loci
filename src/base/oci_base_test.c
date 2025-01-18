
#include "oci_base_test.h"
#include <stdio.h>
#include <string.h>

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

void test_end(Test_Context *ctx) {
    printf("\n=== Test Suite: %s Complete ===\n", ctx->name.str);
    printf("Tests run: %u\n", ctx->tests_run);
    printf("Tests failed: %u\n", ctx->tests_failed);
    printf("Success rate: %.1f%%\n", (ctx->tests_run - ctx->tests_failed) * 100.0f / ctx->tests_run);
}
