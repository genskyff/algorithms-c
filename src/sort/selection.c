#include "selection.h"
#include "utils.h"

void selection_sort(elem_t *arr, size_t len) {
    if (len == 0) {
        return;
    }

    for (size_t i = 0; i < len - 1; i++) {
        size_t min = i;

        for (size_t j = i + 1; j < len; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }

        swap(arr, i, min);
    }
}
