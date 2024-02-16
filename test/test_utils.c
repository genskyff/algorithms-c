#include "test.h"
#include "utils.h"

bool test_swap(void) {
    Array arr = INIT_ARRAY(ARR_LEN);
    copy(&arr, &ARR);
    swap(&arr, 0, arr.len - 1);
    return assert_eq(&arr, &ARR_SWAP_0_10);
}

bool test_copy(void) {
    Array arr = INIT_ARRAY(ARR_LEN);
    copy(&arr, &ARR);
    return assert_eq(&arr, &ARR);
}

bool test_copy_slice(void) {
    Array arr = INIT_ARRAY(ARR_SLICE_4_7_LEN);
    copy_slice(&arr, 0, arr.len, &ARR, 4, 7);
    return assert_eq(&arr, &ARR_SLICE_4_7);
}

bool test_rotate_left(void) {
    Array arr = INIT_ARRAY(ARR_LEN);
    copy(&arr, &ARR);
    rotate_left(&arr, 2);
    return assert_eq(&arr, &ARR_ROTATE_LEFT_2);
}

bool test_rotate_right(void) {
    Array arr = INIT_ARRAY(ARR_LEN);
    copy(&arr, &ARR);
    rotate_right(&arr, 2);
    return assert_eq(&arr, &ARR_ROTATE_RIGHT_2);
}

bool test_rotate_left_slice(void) {
    Array arr = INIT_ARRAY(ARR_LEN);
    copy(&arr, &ARR);
    rotate_left_slice(&arr, 4, 7, 2);
    return assert_eq(&arr, &ARR_ROTATE_LEFT_SLICE_4_7_2);
}

bool test_rotate_right_slice(void) {
    Array arr = INIT_ARRAY(ARR_LEN);
    copy(&arr, &ARR);
    rotate_right_slice(&arr, 4, 7, 2);
    return assert_eq(&arr, &ARR_ROTATE_RIGHT_SLICE_4_7_2);
}

int main(void) {
    run_test(test_swap, "test_swap\t\t");
    run_test(test_copy, "test_copy\t\t");
    run_test(test_copy_slice, "test_copy_slice\t");
    run_test(test_rotate_left, "test_rotate_left\t");
    run_test(test_rotate_right, "test_rotate_right\t");
    run_test(test_rotate_left_slice, "test_rotate_left_slice");
    run_test(test_rotate_right_slice, "test_rotate_right_slice");

    return 0;
}
