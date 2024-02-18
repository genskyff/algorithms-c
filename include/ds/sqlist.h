
#ifndef SQLIST_H
#define SQLIST_H
#include "type.h"
#include <stdbool.h>
#include <stddef.h>

#define MAXSIZE 100

typedef struct {
    elem_t data[MAXSIZE];
    size_t len;
} SqList;

void new();
void show(SqList list);
void clear(SqList *list);
bool is_empty(SqList list);
bool get(SqList list, size_t i, elem_t *e);
bool find(SqList list, elem_t e, size_t *i);
bool insert(SqList *list, size_t i, elem_t e);
bool update(SqList *list, size_t i, elem_t e);
bool delete(SqList *list, size_t i, elem_t *e);

#endif
