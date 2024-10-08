#include "linked_list.h"
#include "util.h"
#include <stdarg.h>
#include <stdlib.h>

LinkedList create(void) {
    LinkedList list = {.head = NULL, .tail = NULL, .len = 0};

    return list;
}

LinkedList init(size_t n, ...) {
    LinkedList list = create();

    va_list ap;
    va_start(ap, n);

    for (size_t i = 0; i < n; i++) {
        Node *node = (Node *)malloc(sizeof(Node));
        _has_alloc_err(node, __func__);

        node->data = va_arg(ap, elem_t);
        node->next = NULL;

        if (list.head == NULL) {
            node->prev = NULL;
            list.head  = node;
        } else {
            node->prev      = list.tail;
            list.tail->next = node;
        }

        list.tail = node;
        list.len++;
    }

    va_end(ap);

    return list;
}

void swap(LinkedList *list, size_t i, size_t j) {
    if (is_empty(list) || i == j || MAX(i, j) >= list->len) {
        return;
    }

    if (i > j) {
        SWAP(i, j);
    }

    Node *node_i, *node_j;
    Node *node = list->head;
    for (size_t k = 0; k <= j; k++) {
        if (k == i) {
            node_i = node;
        }

        if (k == j) {
            node_j = node;
        }

        node = node->next;
    }

    Node *i_prev = node_i->prev;
    Node *i_next = node_i->next;
    Node *j_prev = node_j->prev;
    Node *j_next = node_j->next;

    // adjacent nodes
    if (i_next == node_j) { // node_i is directly connected to node_j
        node_i->next = j_next;
        if (j_next != NULL) {
            j_next->prev = node_i;
        }

        node_j->prev = i_prev;
        if (i_prev != NULL) {
            i_prev->next = node_j;
        }

        node_j->next = node_i;
        node_i->prev = node_j;
    } else { // non-adjacent nodes
        if (i_prev != NULL) {
            i_prev->next = node_j;
        }

        if (i_next != NULL) {
            i_next->prev = node_j;
        }

        if (j_prev != NULL) {
            j_prev->next = node_i;
        }

        if (j_next != NULL) {
            j_next->prev = node_i;
        }

        node_i->prev = j_prev;
        node_j->prev = i_prev;

        Node *tmp    = node_i->next;
        node_i->next = node_j->next;
        node_j->next = tmp;
    }

    if (list->head == node_i) {
        list->head = node_j;
    } else if (list->head == node_j) {
        list->head = node_i;
    }

    if (list->tail == node_i) {
        list->tail = node_j;
    } else if (list->tail == node_j) {
        list->tail = node_i;
    }
}

void reverse(LinkedList *list) {
    if (is_empty(list) || list->len < 2) {
        return;
    }

    for (size_t i = 0; i < list->len / 2; i++) {
        swap(list, i, list->len - i - 1);
    }
}

void show(FILE *stream, LinkedList *list) {
    if (list != NULL) {
        _show_list(stream, list->head, FORWARD, NULL);
    } else {
        _show_list(stream, NULL, FORWARD, NULL);
    }
}

void clear(LinkedList *list) {
    if (!is_empty(list)) {
        Node *node = list->head;
        while (node != NULL) {
            Node *tmp = node;
            node      = node->next;
            free(tmp);
        }

        list->head = NULL;
        list->tail = NULL;
        list->len  = 0;
    }
}

bool is_empty(LinkedList *list) {
    return list == NULL || list->head == NULL || list->tail == NULL ||
           list->len == 0;
}

bool get(LinkedList *list, size_t i, elem_t *e) {
    if (is_empty(list) || i >= list->len) {
        return false;
    }

    Node *node;
    if (i <= (list->len + 1) / 2) {
        node = list->head;
        for (size_t j = 0; j < i; j++) {
            node = node->next;
        }
    } else {
        node = list->tail;
        for (size_t j = list->len - 1; j > i; j--) {
            node = node->prev;
        }
    }

    if (e != NULL) {
        *e = node->data;
    }

    return true;
}

bool first(LinkedList *list, elem_t *e) {
    if (is_empty(list)) {
        return false;
    }

    if (e != NULL) {
        *e = list->head->data;
    }

    return true;
}

bool last(LinkedList *list, elem_t *e) {
    if (is_empty(list)) {
        return false;
    }

    if (e != NULL) {
        *e = list->tail->data;
    }

    return true;
}

bool set(LinkedList *list, size_t i, elem_t e) {
    if (is_empty(list) || i >= list->len) {
        return false;
    }

    Node *node;
    if (i <= (list->len + 1) / 2) {
        node = list->head;
        for (size_t j = 0; j < i; j++) {
            node = node->next;
        }
    } else {
        node = list->tail;
        for (size_t j = list->len - 1; j > i; j--) {
            node = node->prev;
        }
    }

    node->data = e;

    return true;
}

bool find(LinkedList *list, elem_t e, size_t *i) {
    if (is_empty(list)) {
        return false;
    }

    Node *node = list->head;
    for (size_t j = 0; node != NULL && j < list->len; j++) {
        if (node->data == e) {
            if (i != NULL) {
                *i = j;
            }
            return true;
        }
        node = node->next;
    }

    return false;
}

bool insert(LinkedList *list, size_t i, elem_t e) {
    if (list == NULL || i > list->len) {
        return false;
    }

    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        return false;
    }
    node->data = e;

    if (i == 0) {
        node->next = list->head;
        node->prev = NULL;

        if (list->head != NULL) {
            list->head->prev = node;
        }

        list->head = node;

        if (list->len == 0) {
            list->tail = node;
        }
    } else if (i == list->len) {
        node->next = NULL;
        node->prev = list->tail;

        if (list->tail != NULL) {
            list->tail->next = node;
        } else {
            list->head = node;
        }

        list->tail = node;
    } else {
        Node *target;
        if (i <= (list->len + 1) / 2) {
            target = list->head;
            for (size_t j = 0; j < i - 1; j++) {
                target = target->next;
            }
        } else {
            target = list->tail;
            for (size_t j = list->len - 1; j > i; j--) {
                target = target->prev;
            }
        }

        node->next       = target->next;
        node->prev       = target;
        target->next     = node;
        node->next->prev = node;
    }

    list->len++;

    return true;
}

bool push_front(LinkedList *list, elem_t e) {
    return insert(list, 0, e);
}

bool push_back(LinkedList *list, elem_t e) {
    return list != NULL && insert(list, list->len, e);
}

bool del(LinkedList *list, size_t i, elem_t *e) {
    if (is_empty(list) || i >= list->len) {
        return false;
    }

    Node *node;
    if (i <= (list->len + 1) / 2) {
        node = list->head;
        for (size_t j = 0; j < i; j++) {
            node = node->next;
        }
    } else {
        node = list->tail;
        for (size_t j = list->len - 1; j > i; j--) {
            node = node->prev;
        }
    }

    if (e != NULL) {
        *e = node->data;
    }

    if (node->prev == NULL) {
        list->head = node->next;
    } else {
        node->prev->next = node->next;
    }

    if (node->next == NULL) {
        list->tail = node->prev;
    } else {
        node->next->prev = node->prev;
    }

    list->len--;
    free(node);

    return true;
}

bool pop_front(LinkedList *list, elem_t *e) {
    return del(list, 0, e);
}

bool pop_back(LinkedList *list, elem_t *e) {
    return !is_empty(list) && del(list, list->len - 1, e);
}
