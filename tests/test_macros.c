
void test_macros() {
    TEST_INIT("Test macros");

    TEST_BEGIN("KB macro");
    u64 three_kb = KB(3);
    TEST_ASSERT_U32(3 * 1024, three_kb, "Should be equal");

    TEST_BEGIN("MB macro");
    u64 five_mb = MB(5);
    TEST_ASSERT_U32(5 * 1024 * 1024, five_mb, "Should be equal");

    TEST_BEGIN("GB macro");
    u64 ten_gb = GB(10);
    TEST_ASSERT_U64((u64)10 * 1024 * 1024 * 1024, ten_gb, "Should be equal");

    TEST_BEGIN("TB macro");
    u64 one_tb = TB(1);
    TEST_ASSERT_U64((u64)1 * 1024 * 1024 * 1024 * 1024, one_tb, "Should be equal");

    TEST_END();
}

TEST_REGISTER(test_macros);
