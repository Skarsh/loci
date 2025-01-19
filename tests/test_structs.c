#include "base/oci_base_test.h"

typedef struct {
    i32 x;
    i32 y;
    f32 scale;
} Point;

void test_struct_comparisons(void) {
    TEST_INIT("Struct Comparisons");

    // Test equal structs
    TEST_BEGIN("equal structs");
    Point p1 = {10, 20, 1.5f};
    Point p2 = {10, 20, 1.5f};
    TEST_ASSERT_STRUCT(p1, p2, Point, "Points should be equal");

    // Test unequal structs
    TEST_BEGIN("unequal structs");
    Point p3 = {10, 20, 1.5f};
    Point p4 = {10, 25, 1.5f}; // Different y value
    TEST_ASSERT_STRUCT_NOT_EQUAL(p3, p4, Point, "Points should be different");

    TEST_END();
}

// Register the test function
TEST_REGISTER(test_struct_comparisons);
