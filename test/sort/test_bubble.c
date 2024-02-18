#include "bubble.h"
#include "test.h"
#include <stdlib.h>

TestData DATA[DATA_LEN];

bool test_bubble_sort(void) {
    bool all_passed = true;

    for (size_t i = 0; i < DATA_LEN; i++) {
        elem_t *data = (elem_t *)malloc(DATA[i].unsorted.len * sizeof(elem_t));
        Array   arr  = {data, DATA[i].unsorted.len};
        copy(&arr, &DATA[i].unsorted);
        bubble_sort(&arr);
        all_passed = assert_eq(arr, DATA[i].sorted);
        free(data);
    }

    return all_passed;
}

bool test_cocktail_sort(void) {
    bool all_passed = true;

    for (size_t i = 0; i < DATA_LEN; i++) {
        elem_t *data = (elem_t *)malloc(DATA[i].unsorted.len * sizeof(elem_t));
        Array   arr  = {data, DATA[i].unsorted.len};
        copy(&arr, &DATA[i].unsorted);
        cocktail_sort(&arr);
        all_passed = assert_eq(arr, DATA[i].sorted);
        free(data);
    }

    return all_passed;
}

int main(void) {
    init_data(DATA);
    run_test(test_bubble_sort, "test_bubble_sort\t");
    run_test(test_cocktail_sort, "test_cocktail_sort\t");

    return 0;
}
