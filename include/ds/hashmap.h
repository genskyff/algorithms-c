#ifndef HASHMAP_H
#define HASHMAP_H

#include "type.h"
#include <stdbool.h>

#define INIT_CAP      100
#define SHINK_CAP     1000
#define BUCKET_CAP    10
#define LOW_FACTOR    0.25
#define LOAD_FACTOR   0.75
#define GROWTH_FACTOR 2

typedef char  *key_t;
typedef elem_t value_t;

typedef struct Pair {
    key_t        key;
    value_t      value;
    struct Pair *next;
} Pair;

// separate chaining
typedef struct {
    Pair  *head;
    size_t len;
} Bucket;

typedef struct {
    Bucket *buckets;
    size_t  len;
    size_t  cap;
} HashMap;

HashMap  create(void);
HashMap  create_with(size_t cap);
HashMap  init(key_t *keys, value_t *values, size_t len);
void     show(FILE *stream, HashMap *map);
void     show_keys(FILE *stream, HashMap *map);
void     show_values(FILE *stream, HashMap *map);
void     clear(HashMap *map);
bool     is_empty(HashMap *map);
key_t   *get_keys(HashMap *map);
value_t *get_values(HashMap *map);
bool     get(HashMap *map, key_t key, value_t *value);
bool     insert(HashMap *map, key_t key, value_t value);
bool     del(HashMap *map, key_t key);
void     drop(HashMap *map);

#endif
