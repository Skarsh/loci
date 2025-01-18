#include "base/oci_base_test.h"
#include "base/oci_base_string.h"

void test_string_operations(void) {
    TEST_INIT("String Operations");

    // Test string length
    TEST_BEGIN("string length");
    char *test_str = "hello";
    String8 str = str8((u8*)test_str, strlen(test_str));
    TEST_ASSERT_INT(5, str.size, "String length should be 5");

    // Test string comparison
    TEST_BEGIN("string comparison");
    char *test_str2 = "hello";
    String8 str2 = str8((u8*)test_str2, strlen(test_str2));
    TEST_ASSERT(str.size == str2.size && 
                memcmp(str.str, str2.str, str.size) == 0,
                "Strings should be equal");

    TEST_END();
}

TEST_REGISTER(test_string_operations);

