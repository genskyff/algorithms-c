#ifndef SQLIST_H
#define SQLIST_H
#include "type.h"
#include <stdbool.h>
#include <stdio.h>

#define MAXLEN 100

typedef struct {
    elem_t data[MAXLEN];
    size_t len;
} SqList;

SqList create(void);
SqList init(size_t n, ...);
void   swap(SqList *list, size_t i, size_t j);
void   reverse(SqList *list);
void   show(FILE *stream, SqList *list);
void   clear(SqList *list);
bool   is_empty(SqList *list);
bool   get(SqList *list, size_t i, elem_t *e);
bool   set(SqList *list, size_t i, elem_t e);
bool   find(SqList *list, elem_t e, size_t *i);
bool   insert(SqList *list, size_t i, elem_t e);
bool   push(SqList *list, elem_t e);
bool   del(SqList *list, size_t i, elem_t *e);
bool   pop(SqList *list, elem_t *e);

#endif
