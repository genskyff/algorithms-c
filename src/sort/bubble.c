#include "bubble.h"
#include "utils.h"

// 冒泡排序
void bubble_sort(int a[], int len) {
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                swap(a, j, j + 1);
            }
        }
    }
}
