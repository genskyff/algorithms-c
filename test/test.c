#include "test.h"
#include "utils.h"
#include <stdlib.h>

void init_sort_data(TestSortData *data) {
    elem_t one[]            = {0};
    elem_t unsorted_2[]     = {5, -2};
    elem_t sorted_2[]       = {-2, 5};
    elem_t unsorted_3[]     = {3, -1, 0};
    elem_t sorted_3[]       = {-1, 0, 3};
    elem_t unsorted[]       = {-3, -5, 2, 1, 4, 3, 0, 5, 1, -1, -2, -4};
    elem_t sorted[]         = {-5, -4, -3, -2, -1, 0, 1, 1, 2, 3, 4, 5};
    elem_t sorted_reverse[] = {5, 4, 3, 2, 1, 1, 0, -1, -2, -3, -4, -5};

    data[0].unsorted = NULL;
    data[0].sorted   = NULL;
    data[0].len      = 0;

    elem_t *tmp = (elem_t *)malloc(2 * sizeof(one));
    size_t  len = sizeof(one) / sizeof(elem_t);
    copy(tmp, len, one, len);
    data[1].unsorted = tmp;
    copy(tmp + len, len, one, len);
    data[1].sorted = tmp + len;
    data[1].len    = len;

    tmp = (elem_t *)malloc(2 * sizeof(unsorted_2));
    len = sizeof(unsorted_2) / sizeof(elem_t);
    copy(tmp, len, unsorted_2, len);
    data[2].unsorted = tmp;
    copy(tmp + len, len, sorted_2, len);
    data[2].sorted = tmp + len;
    data[2].len    = len;

    tmp = (elem_t *)malloc(2 * sizeof(unsorted_3));
    len = sizeof(unsorted_3) / sizeof(elem_t);
    copy(tmp, len, unsorted_3, len);
    data[3].unsorted = tmp;
    copy(tmp + len, len, sorted_3, len);
    data[3].sorted = tmp + len;
    data[3].len    = len;

    tmp = (elem_t *)malloc(2 * sizeof(unsorted));
    len = sizeof(unsorted) / sizeof(elem_t);
    copy(tmp, len, unsorted, len);
    data[4].unsorted = tmp;
    copy(tmp + len, len, sorted, len);
    data[4].sorted = tmp + len;
    data[4].len    = len;

    tmp = (elem_t *)malloc(2 * sizeof(sorted));
    len = sizeof(sorted) / sizeof(elem_t);
    copy(tmp, len, sorted, len);
    data[5].unsorted = tmp;
    copy(tmp + len, len, sorted, len);
    data[5].sorted = tmp + len;
    data[5].len    = len;

    tmp = (elem_t *)malloc(2 * sizeof(sorted_reverse));
    len = sizeof(sorted_reverse) / sizeof(elem_t);
    copy(tmp, len, sorted_reverse, len);
    data[6].unsorted = tmp;
    copy(tmp + len, len, sorted, len);
    data[6].sorted = tmp + len;
    data[6].len    = len;
}

void run_test(TestFunc test, const char *prefix, const char *test_name) {
    if (prefix == NULL || *prefix == '\0') {
        prefix = "test";
    }

    printf("%s %s\t", prefix, test_name);

    if (test()) {
        printf("\x1b[1;32m...OK\x1b[0m\n");
    }
}

bool assert_array_eq(elem_t *left, size_t l_len, elem_t *right, size_t r_len) {
    bool is_eq = true;

    if (l_len != r_len) {
        is_eq = false;
    } else {
        for (size_t i = 0; i < l_len; i++) {
            if (left[i] != right[i]) {
                is_eq = false;
                break;
            }
        }
    }

    if (!is_eq) {
        fprintf(stderr, "\x1b[1;31m...FAILED\x1b[0m\n");
        fprintf(stderr, "  |-- left\t");
        show(stderr, left, l_len);
        fprintf(stderr, "  |-- right\t");
        show(stderr, right, r_len);
        fprintf(stderr, "\n");
        abort();
    }

    return is_eq;
}
