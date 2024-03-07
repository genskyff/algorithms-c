#include "hashmap.h"
#include "util.h"
#include <stdlib.h>

typedef void (*PrintFunc)(FILE *stream, Pair *p);
void _print(FILE *stream, HashMap *map, PrintFunc print_func,
            const char *prefix, const char *suffix, const char *sep) {
    if (stream == NULL) {
        stream = stdout;
    }

    if (map == NULL || map->len == 0) {
        fprintf(stream, "%s%s\n", prefix, suffix);
        return;
    }

    fprintf(stream, "%s", prefix);
    bool first_entry = true;
    for (size_t i = 0; i < map->cap; ++i) {
        Pair *p = map->bucket[i];
        if (p == NULL) {
            continue;
        }

        if (first_entry) {
            first_entry = false;
        } else {
            fprintf(stream, "%s", sep);
        }

        if (p->next != NULL) {
            fprintf(stream, "%s", prefix);
        }

        while (p != NULL) {
            print_func(stream, p);
            if (p->next != NULL) {
                fprintf(stream, "%s", sep);
            }
            p = p->next;
        }

        if (map->bucket[i]->next != NULL) {
            fprintf(stream, "%s", suffix);
        }
    }
    fprintf(stream, "%s\n", suffix);
}

void _print_pair(FILE *stream, Pair *p) {
    fprintf(stream, "\"%s\": %d", p->key, p->value);
}

void _print_key(FILE *stream, Pair *p) {
    fprintf(stream, "\"%s\"", p->key);
}

void _print_value(FILE *stream, Pair *p) {
    fprintf(stream, "%d", p->value);
}

// FNV-1a hash
uint64_t _hash(const char *str) {
    uint64_t prime        = 1099511628211ULL;
    uint64_t offset_basis = 14695981039346656037ULL;
    uint64_t hash         = offset_basis;

    while (*str != '\0') {
        hash = hash ^ (uint8_t)*str;
        hash = hash * prime;
        str++;
    }

    return hash;
}

bool _shrink(HashMap *map) {
    size_t new_cap     = map->cap / GROWTH_FACTOR;
    Pair **new_buckets = (Pair **)calloc(new_cap, sizeof(Pair *));
    if (new_buckets == NULL) {
        return false;
    }

    for (size_t i = 0; i < map->cap; ++i) {
        Pair *p = map->bucket[i];
        while (p != NULL) {
            Pair *tmp = p;
            p         = p->next;

            size_t idx       = (size_t)_hash(tmp->key) % new_cap;
            tmp->next        = new_buckets[idx];
            new_buckets[idx] = tmp;
        }
    }

    free(map->bucket);
    map->bucket = new_buckets;
    map->cap    = new_cap;

    return true;
}

bool _grow(HashMap *map);

HashMap create(void) {
    return init(NULL, NULL, 0);
}

HashMap init(key_t *keys, value_t *values, size_t len) {
    size_t cap =
        keys == NULL || values == NULL || len < (size_t)(INIT_CAP * LOAD_FACTOR)
            ? INIT_CAP
            : len * GROWTH_FACTOR;
    Pair **buckets = (Pair **)calloc(cap, sizeof(Pair *));

    if (buckets == NULL) {
        fprintf(stderr,
                "\x1b[1;31merror: \x1b[0mfailed to allocate memory (exec "
                "\x1b[33minit\x1b[0m)\n\n");
        exit(EXIT_FAILURE);
    }

    HashMap map = {.bucket = buckets, .len = 0, .cap = cap};

    if (keys == NULL || values == NULL || len == 0) {
        return map;
    }

    for (size_t i = 0; i < len; i++) {
        size_t idx = (size_t)_hash(keys[i]) % cap;

        bool has_key = false;
        if (map.bucket[idx] != NULL) {
            Pair *tmp = map.bucket[idx];
            while (tmp != NULL) {
                if (tmp->key == keys[i]) {
                    tmp->value = values[i];
                    has_key    = true;
                    break;
                }
                tmp = tmp->next;
            }
        }

        if (!has_key) {
            Pair *p = (Pair *)malloc(sizeof(Pair));
            if (p == NULL) {
                return map;
            }

            p->key          = keys[i];
            p->value        = values[i];
            p->next         = map.bucket[idx];
            map.bucket[idx] = p;
            map.len++;
        }
    }

    return map;
}

void show(FILE *stream, HashMap *map) {
    _print(stream, map, _print_pair, "{", "}", ", ");
}

void show_keys(FILE *stream, HashMap *map) {
    _print(stream, map, _print_key, "[", "]", ", ");
}

void show_values(FILE *stream, HashMap *map) {
    _print(stream, map, _print_value, "[", "]", ", ");
}

void clear(HashMap *map) {
    if (map == NULL) {
        return;
    }

    for (size_t i = 0; i < map->cap; ++i) {
        Pair *p = map->bucket[i];
        while (p != NULL) {
            Pair *tmp = p;
            p         = p->next;
            free(tmp);
        }
        map->bucket[i] = NULL;
    }
    map->len = 0;
}

bool is_empty(HashMap *map) {
    return map == NULL || map->len == 0;
}

key_t *get_keys(HashMap *map) {
    if (map == NULL || map->len == 0) {
        return NULL;
    }

    key_t *keys = (key_t *)malloc(map->len * sizeof(key_t));
    if (keys == NULL) {
        return NULL;
    }

    for (size_t i = 0, idx = 0; i < map->cap; ++i) {
        Pair *p = map->bucket[i];
        while (p != NULL) {
            keys[idx++] = p->key;
            p           = p->next;
        }
    }

    return keys;
}

value_t *get_values(HashMap *map) {
    if (map == NULL || map->len == 0) {
        return NULL;
    }

    value_t *values = (value_t *)malloc(map->len * sizeof(value_t));
    if (values == NULL) {
        return NULL;
    }

    for (size_t i = 0, idx = 0; i < map->cap; ++i) {
        Pair *p = map->bucket[i];
        while (p != NULL) {
            values[idx++] = p->value;
            p             = p->next;
        }
    }

    return values;
}

bool get(HashMap *map, key_t key, value_t *value) {
    if (map == NULL || map->len == 0) {
        return false;
    }

    size_t idx = (size_t)_hash(key) % map->cap;
    Pair  *p   = map->bucket[idx];
    while (p != NULL) {
        if (_cmp_str(p->key, key) == 0) {
            if (value != NULL) {
                *value = p->value;
            }
            return true;
        }
        p = p->next;
    }

    return false;
}

bool insert(HashMap *map, key_t key, value_t value) {
    if (map == NULL) {
        return false;
    }

    if (map->len >= (size_t)(map->cap * LOAD_FACTOR)) {
        size_t new_cap     = map->cap * GROWTH_FACTOR;
        Pair **new_buckets = (Pair **)calloc(new_cap, sizeof(Pair *));
        if (new_buckets == NULL) {
            return false;
        }

        for (size_t i = 0; i < map->cap; ++i) {
            Pair *p = map->bucket[i];
            while (p != NULL) {
                Pair *tmp = p;
                p         = p->next;

                size_t idx       = (size_t)_hash(tmp->key) % new_cap;
                tmp->next        = new_buckets[idx];
                new_buckets[idx] = tmp;
            }
        }

        free(map->bucket);
        map->bucket = new_buckets;
        map->cap    = new_cap;
    }

    size_t idx = (size_t)_hash(key) % map->cap;
    Pair  *p   = map->bucket[idx];
    while (p != NULL) {
        if (_cmp_str(p->key, key) == 0) {
            p->value = value;
            return true;
        }
        p = p->next;
    }

    Pair *new_pair = (Pair *)malloc(sizeof(Pair));
    if (new_pair == NULL) {
        return false;
    }

    new_pair->key    = key;
    new_pair->value  = value;
    new_pair->next   = map->bucket[idx];
    map->bucket[idx] = new_pair;
    map->len++;

    return true;
}

bool del(HashMap *map, key_t key);

void drop(HashMap *map);
