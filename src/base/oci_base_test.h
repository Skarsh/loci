#ifndef OCI_BASE_TEST_H
#define OCI_BASE_TEST_H

#include "oci_base_core.h"
#include "oci_base_string.h"

typedef struct {
    String8 name;
    u32 tests_run;
    u32 tests_failed;
    String8 current_test;
} Test_Context;

// Initialize test context
void test_init(Test_Context *ctx, const String8 name);

// Begin a new test case
void test_begin(Test_Context *ctx, const String8 test_name);

// Assert functions
void test_assert(Test_Context *ctx, b32 condition, const String8 message);
void test_assert_equal_int(Test_Context *ctx, i32 expected, i32 actual, const String8 message);
void test_assert_equal_str(Test_Context *ctx, const String8 expected, const String8 actual, const String8 message);

// Print test results
void test_end(Test_Context *ctx);

// Macros for easier test writing
#define TEST_INIT(name) \
    Test_Context ctx = {0}; \
    test_init(&ctx, name)

#define TEST_BEGIN(name) test_begin(&ctx, name)
#define TEST_ASSERT(condition, message) test_assert(&ctx, condition, message)
#define TEST_ASSERT_INT(expected, actual, message) test_assert_equal_int(&ctx, expected, actual, message)
#define TEST_ASSERT_STR(expected, actual, message) test_assert_equal_str(&ctx, expected, actual, message)

#define TEST_END() test_end(&ctx)

#endif // OCI_BASE_TEST_H 
