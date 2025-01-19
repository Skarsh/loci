#ifndef OCI_BASE_TEST_H
#define OCI_BASE_TEST_H

// TODO(Thomas): Should be able to remove these too

typedef struct {
    String8 name;
    u32 tests_run;
    u32 tests_failed;
    String8 current_test;
} Test_Context;

typedef void (*Test_Func)(void);

struct Test_Entry;
typedef struct Test_Entry Test_Entry;

struct Test_Entry {
    String8 name;
    Test_Func func;
    Test_Entry* next;
};

void test_register(String8 name, Test_Func func);

void test_run_all();

void test_init(Test_Context *ctx, String8 name);

void test_begin(Test_Context *ctx, String8 test_name);

void test_assert(Test_Context *ctx, b32 condition, String8 message);

void test_assert_equal_i32(Test_Context *ctx, i32 expected, i32 actual, String8 message);
void test_assert_equal_i64(Test_Context *ctx, i64 expected, i64 actual, String8 message);
void test_assert_equal_u32(Test_Context *ctx, u32 expected, u32 actual, String8 message);
void test_assert_equal_u64(Test_Context *ctx, u64 expected, u64 actual, String8 message);

void test_assert_equal_str(Test_Context *ctx, String8 expected, String8 actual, String8 message);
void test_assert_equal_mem(Test_Context *ctx, const void *a, const void *b, 
                          usize size, const String8 type_name, const String8 message, 
                          b32 expect_equal);

void test_end(Test_Context *ctx);

#define TEST_INIT(name_str) \
    Test_Context ctx = {0}; \
    test_init(&ctx, str8_lit(name_str))

#define TEST_BEGIN(name_str) test_begin(&ctx, str8_lit(name_str))
#define TEST_ASSERT(condition, message_str) test_assert(&ctx, condition, str8_lit(message_str))

#define TEST_ASSERT_I32(expected, actual, message_str) \
    test_assert_equal_i32(&ctx, expected, actual, str8_lit(message_str))

#define TEST_ASSERT_I64(expected, actual, message_str) \
    test_assert_equal_i64(&ctx, expected, actual, str8_lit(message_str))

#define TEST_ASSERT_U32(expected, actual, message_str) \
    test_assert_equal_u32(&ctx, expected, actual, str8_lit(message_str))

#define TEST_ASSERT_U64(expected, actual, message_str) \
    test_assert_equal_u64(&ctx, expected, actual, str8_lit(message_str))

#define TEST_ASSERT_STR(expected, actual, message_str) \
    test_assert_equal_str(&ctx, expected, actual, str8_lit(message_str))

#define TEST_ASSERT_STRUCT(expected, actual, type, message_str) \
    test_assert_equal_mem(&ctx, &(expected), &(actual), sizeof(type), \
                         str8_lit(#type), str8_lit(message_str), true)

#define TEST_ASSERT_STRUCT_NOT_EQUAL(a, b, type, message_str) \
    test_assert_equal_mem(&ctx, &(a), &(b), sizeof(type), \
                         str8_lit(#type), str8_lit(message_str), false)

#define TEST_END() test_end(&ctx)

#define TEST_REGISTER(func) \
    void __attribute__((constructor)) register_##func(void) { \
        test_register(str8_lit(#func), func); \
    }

#endif // OCI_BASE_TEST_H
