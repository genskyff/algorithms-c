#include "helper.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>

void run_test(TestFunc test, char *mod, char *target, char *test_name) {
    bool is_mod       = mod != NULL && *mod != '\0';
    bool is_target    = target != NULL && *target != '\0';
    bool is_test_name = test_name != NULL && *test_name != '\0';

    printf("test %s%s%s%s%s%s", is_mod ? mod : "", is_mod ? " " : "",
           is_target ? target : "", is_target ? " " : "",
           is_test_name ? test_name : "", is_test_name ? " " : "");

    test();
    printf("\x1b[1;32m ... OK\x1b[0m\n");
}

void assert(bool cond, char *msg) {
    if (!cond) {
        char *_msg = (msg == NULL || *msg == '\0') ? "\"\"" : msg;
        fprintf(stderr, "\x1b[1;31m ... FAILED\x1b[0m\n");
        fprintf(stderr, "\x1b[33m|-- message: \x1b[0m%s\n", _msg);
        fprintf(stderr, "\x1b[33m|-- expect:  \x1b[0mtrue\n");
        fprintf(stderr, "\x1b[33m|-- actual:  \x1b[0mfalse\n\n");
        exit(EXIT_FAILURE);
    }
}

void assert_not(bool cond, char *msg) {
    return assert(!cond, msg);
}

bool _is_eq(elem_t left, elem_t right) {
    return left == right;
}

void _err_msg(elem_t left, elem_t right, char *msg) {
    char *_msg = (msg == NULL || *msg == '\0') ? "\"\"" : msg;
    fprintf(stderr, "\x1b[1;31m ... FAILED\x1b[0m\n");
    fprintf(stderr, "\x1b[33m|-- message: \x1b[0m%s\n", _msg);
    fprintf(stderr, "\x1b[33m|-- left:    \x1b[0m");
    fprintf(stderr, "%d\n", left);
    fprintf(stderr, "\x1b[33m|-- right:   \x1b[0m");
    fprintf(stderr, "%d\n\n", right);
    exit(EXIT_FAILURE);
}

void assert_eq(elem_t left, elem_t right, char *msg) {
    if (!_is_eq(left, right)) {
        _err_msg(left, right, msg);
    }
}

void assert_ne(elem_t left, elem_t right, char *msg) {
    if (_is_eq(left, right)) {
        _err_msg(left, right, msg);
    }
}

bool _is_arr_eq(elem_t *left, size_t l_len, elem_t *right, size_t r_len) {
    if (left == NULL && right == NULL) {
        return true;
    }

    if (left == NULL || right == NULL || l_len != r_len) {
        return false;
    }

    for (size_t i = 0; i < l_len; i++) {
        if (left[i] != right[i]) {
            return false;
        }
    }

    return true;
}

void _arr_err_msg(elem_t *left, size_t l_len, elem_t *right, size_t r_len,
                  char *msg) {
    char *_msg = (msg == NULL || *msg == '\0') ? "\"\"" : msg;
    fprintf(stderr, "\x1b[1;31m ... FAILED\x1b[0m\n");
    fprintf(stderr, "\x1b[33m|-- message: \x1b[0m%s\n", _msg);
    fprintf(stderr, "\x1b[33m|-- left:    \x1b[0m");
    _show(stderr, left, l_len, NULL);
    fprintf(stderr, "\x1b[33m|-- right:   \x1b[0m");
    _show(stderr, right, r_len, NULL);
    fprintf(stderr, "\n");
    exit(EXIT_FAILURE);
}

void assert_arr_eq(elem_t *left, size_t l_len, elem_t *right, size_t r_len,
                   char *msg) {
    if (!_is_arr_eq(left, l_len, right, r_len)) {
        _arr_err_msg(left, l_len, right, r_len, msg);
    }
}

void assert_arr_ne(elem_t *left, size_t l_len, elem_t *right, size_t r_len,
                   char *msg) {
    if (_is_arr_eq(left, l_len, right, r_len)) {
        _arr_err_msg(left, l_len, right, r_len, msg);
    }
}

bool _is_list_eq(Node *left, Node *right, Direction dir) {
    while (left != NULL && right != NULL) {
        if (left->data != right->data) {
            return false;
        }
        left  = dir == FORWARD ? left->next : left->prev;
        right = dir == FORWARD ? right->next : right->prev;
    }

    return left == NULL && right == NULL;
}

void _list_err_msg(Node *left, Node *right, Direction dir, char *msg) {
    char *_msg = (msg == NULL || *msg == '\0') ? "\"\"" : msg;
    fprintf(stderr, "\x1b[1;31m ... FAILED\x1b[0m\n");
    fprintf(stderr, "\x1b[33m|-- message: \x1b[0m%s\n", _msg);
    fprintf(stderr, "\x1b[33m|-- left:    \x1b[0m");
    _show_list(stderr, left, dir, NULL);
    fprintf(stderr, "\x1b[33m|-- right:   \x1b[0m");
    _show_list(stderr, right, dir, NULL);
    fprintf(stderr, "\n");
    exit(EXIT_FAILURE);
}

void assert_list_eq(Node *left, Node *right, Direction dir, char *msg) {
    if (!_is_list_eq(left, right, dir)) {
        _list_err_msg(left, right, dir, msg);
    }
}

void assert_list_ne(Node *left, Node *right, Direction dir, char *msg) {
    if (_is_list_eq(left, right, dir)) {
        _list_err_msg(left, right, dir, msg);
    }
}

bool _is_list_arr_eq(Node *node, Direction dir, elem_t *arr, size_t len) {
    if (node == NULL && arr == NULL) {
        return true;
    }

    if (node == NULL || arr == NULL) {
        return false;
    }

    for (size_t i = 0; i < len; i++) {
        size_t idx = dir == FORWARD ? i : len - i - 1;
        if (node == NULL || node->data != arr[idx]) {
            return false;
        }
        node = dir == FORWARD ? node->next : node->prev;
    }

    return node == NULL;
}

void _list_arr_err_msg(Node *node, Direction dir, elem_t *arr, size_t len,
                       char *msg) {
    char *_msg = (msg == NULL || *msg == '\0') ? "\"\"" : msg;
    fprintf(stderr, "\x1b[1;31m ... FAILED\x1b[0m\n");
    fprintf(stderr, "\x1b[33m|-- message: \x1b[0m%s\n", _msg);
    fprintf(stderr, "\x1b[33m|-- list:    \x1b[0m");
    _show_list(stderr, node, dir, ", ");
    fprintf(stderr, "\x1b[33m|-- arr:     \x1b[0m");
    _show(stderr, arr, len, NULL);
    fprintf(stderr, "\n");
    exit(EXIT_FAILURE);
}

void assert_list_arr_eq(Node *node, Direction dir, elem_t *arr, size_t len,
                        char *msg) {
    if (!_is_list_arr_eq(node, dir, arr, len)) {
        _list_arr_err_msg(node, dir, arr, len, msg);
    }
}

void assert_list_arr_ne(Node *node, Direction dir, elem_t *arr, size_t len,
                        char *msg) {
    if (_is_list_arr_eq(node, dir, arr, len)) {
        _list_arr_err_msg(node, dir, arr, len, msg);
    }
}

void init_sort_data(TestSortData *data) {
    if (data == NULL) {
        fprintf(stderr, "\x1b[1;31merror: \x1b[0mdata is NULL (exec "
                        "\x1b[33minit_sort_data\x1b[0m)\n\n");
        exit(EXIT_FAILURE);
    }

    elem_t *none             = NULL;
    elem_t  one[1]           = {0};
    elem_t  unsorted_2[2]    = {5, -2};
    elem_t  sorted_2[2]      = {-2, 5};
    elem_t  unsorted_3[3]    = {3, -1, 0};
    elem_t  sorted_3[3]      = {-1, 0, 3};
    elem_t  unsorted[]       = {-3, -5, 2, 1, 4, 3, 0, 5, 1, -1, -2, -4};
    elem_t  sorted[]         = {-5, -4, -3, -2, -1, 0, 1, 1, 2, 3, 4, 5};
    elem_t  sorted_reverse[] = {5, 4, 3, 2, 1, 1, 0, -1, -2, -3, -4, -5};

    // none element
    data[0].unsorted = none;
    data[0].sorted   = none;
    data[0].len      = 0;

    // one element
    elem_t *tmp = (elem_t *)malloc(2 * sizeof(one));
    size_t  len = sizeof(one) / sizeof(elem_t);
    _copy(tmp, len, one, len);
    data[1].unsorted = tmp;
    _copy(tmp + len, len, one, len);
    data[1].sorted = tmp + len;
    data[1].len    = len;

    // two unsorted elements
    tmp = (elem_t *)malloc(2 * sizeof(unsorted_2));
    len = sizeof(unsorted_2) / sizeof(elem_t);
    _copy(tmp, len, unsorted_2, len);
    data[2].unsorted = tmp;
    _copy(tmp + len, len, sorted_2, len);
    data[2].sorted = tmp + len;
    data[2].len    = len;

    // three  unsorted elements
    tmp = (elem_t *)malloc(2 * sizeof(unsorted_3));
    len = sizeof(unsorted_3) / sizeof(elem_t);
    _copy(tmp, len, unsorted_3, len);
    data[3].unsorted = tmp;
    _copy(tmp + len, len, sorted_3, len);
    data[3].sorted = tmp + len;
    data[3].len    = len;

    // more than three unsorted elements
    tmp = (elem_t *)malloc(2 * sizeof(unsorted));
    len = sizeof(unsorted) / sizeof(elem_t);
    _copy(tmp, len, unsorted, len);
    data[4].unsorted = tmp;
    _copy(tmp + len, len, sorted, len);
    data[4].sorted = tmp + len;
    data[4].len    = len;

    // sorted reverse elements
    tmp = (elem_t *)malloc(2 * sizeof(sorted_reverse));
    len = sizeof(sorted_reverse) / sizeof(elem_t);
    _copy(tmp, len, sorted_reverse, len);
    data[5].unsorted = tmp;
    _copy(tmp + len, len, sorted, len);
    data[5].sorted = tmp + len;
    data[5].len    = len;

    // sorted elements
    tmp = (elem_t *)malloc(2 * sizeof(sorted));
    len = sizeof(sorted) / sizeof(elem_t);
    _copy(tmp, len, sorted, len);
    data[6].unsorted = tmp;
    _copy(tmp + len, len, sorted, len);
    data[6].sorted = tmp + len;
    data[6].len    = len;
}