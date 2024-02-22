#include "sqlist.h"
#include "utils.h"
#include <stdarg.h>
#include <stdio.h>

SqList sqlist(void) {
    SqList list;
    list.len = 0;

    return list;
}

SqList sqlist_init(size_t n, ...) {
    SqList list = sqlist();

    n = MIN(n, MAXLEN);

    va_list ap;
    va_start(ap, n);

    for (size_t i = 0; i < n; i++) {
        list.data[list.len++] = va_arg(ap, elem_t);
    }

    va_end(ap);

    return list;
}

void show(FILE *stream, SqList *list) {
    if (list != NULL) {
        _show(stream, list->data, list->len);
    }
}

void clear(SqList *list) {
    if (list != NULL) {
        list->len = 0;
    }
}

bool is_empty(SqList *list) {
    return list == NULL || list->len == 0;
}

bool get(SqList *list, size_t i, elem_t *e) {
    if (list == NULL || list->len == 0 || i >= list->len) {
        return false;
    }

    if (e != NULL) {
        *e = list->data[i];
    }

    return true;
}

bool set(SqList *list, size_t i, elem_t e) {
    if (list == NULL || list->len == 0 || i >= list->len) {
        return false;
    }

    list->data[i] = e;

    return true;
}

bool find(SqList *list, elem_t e, size_t *i) {
    return list != NULL && _find(list->data, list->len, e, i);
}

bool insert(SqList *list, size_t i, elem_t e) {
    if (list == NULL || list->len == MAXLEN || i > list->len) {
        return false;
    }

    if (i < list->len) {
        _move_right_slice(list->data, list->len, i, list->len, 1);
    }

    list->data[i] = e;
    list->len++;

    return true;
}

bool push(SqList *list, elem_t e) {
    if (list == NULL || list->len == MAXLEN) {
        return false;
    } else {
        return insert(list, list->len, e);
    }
}

bool del(SqList *list, size_t i, elem_t *e) {
    if (list == NULL || list->len == 0 || i >= list->len) {
        return false;
    }

    if (e != NULL) {
        *e = list->data[i];
    }

    if (i < list->len - 1) {
        _move_left_slice(list->data, list->len, i, list->len, 1);
    }

    list->len--;

    return true;
}

bool pop(SqList *list, elem_t *e) {
    if (list == NULL || list->len == 0) {
        return false;
    } else {
        return del(list, list->len - 1, e);
    }
}
