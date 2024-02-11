#include "insertion.h"

void insertion_sort(int *arr, int len) {
    if (len < 2) {
        return;
    }

    for (int i = 1; i < len; i++) {
        int base = arr[i];
        int j    = i;

        while (j > 0 && arr[j - 1] > base) {
            arr[j] = arr[j - 1];
            j--;
        }

        arr[j] = base;
    }
}

void binary_insertion_sort(int *arr, int len) {
    if (len < 2) {
        return;
    }

    for (int i = 1; i < len; i++) {
        int base  = arr[i];
        int left  = 0;
        int right = i;

        while (left < right) {
            int mid = (left + right) / 2;

            if (arr[mid] > base) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }

        for (int j = i - 1; j >= left; j--) {
            arr[j + 1] = arr[j];
        }

        arr[left] = base;
    }
}

void shell_sort(int *arr, int len) {
    if (len < 2) {
        return;
    }

    int gap = 1;

    while (gap < len / 3) {
        gap = gap * 3 + 1;
    }

    while (gap >= 1) {
        for (int i = gap; i < len; i++) {
            int base = arr[i];
            int j    = i;

            while (j >= gap && arr[j - gap] > base) {
                arr[j] = arr[j - gap];
                j -= gap;
            }

            arr[j] = base;
        }

        gap = (gap - 1) / 3;
    }
}
