
void test_string_operations() {
    TEST_INIT("String Operations");

    // Test string length
    TEST_BEGIN("string length");

    String8 str = str8_lit("hello");
    
    TEST_ASSERT_I32(5, str.size, "String length should be 5");

    // Test string comparison
    TEST_BEGIN("string comparison");
    String8 str2 = str8_lit("hello");
    TEST_ASSERT(str.size == str2.size && memcmp(str.str, str2.str, str.size) == 0, "Strings should be equal");

    TEST_END();
}

TEST_REGISTER(test_string_operations);

