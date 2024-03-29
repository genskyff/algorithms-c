#ifndef TYPE_H
#define TYPE_H

#include <stdio.h>
#define MAXLEN 100

typedef int elem_t;

typedef struct Node {
    elem_t       data;
    struct Node *prev;
    struct Node *next;
} Node;

typedef enum { FORWARD, BACKWARD } Direction;

#endif
