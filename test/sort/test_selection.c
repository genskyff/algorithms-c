#include "data.h"
#include "selection.h"
#include "utils.h"
#include <stdio.h>

void test_selection_sort(void) {
    printf("\n---- test_selection_sort ----\n");

    int arr[LEN];
    copy(UNSTORED, arr, LEN);
    selection_sort(arr, LEN);
    assert_eq(arr, STORED, LEN);
}

int main(void) {
    test_selection_sort();

    return 0;
}
