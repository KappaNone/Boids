#ifndef DA_H
#define DA_H

#include <stdlib.h>
#include <string.h>
#include <stddef.h>


typedef struct DA {
    void *data;
    size_t used;
    size_t size;
    size_t elem_size;
} DA;

void da_init(DA *a, size_t elem_size, size_t init_size);
void da_push(DA *a, void *element);
void *da_get(DA *a, size_t index);
void da_free(DA *a);

#define da_get_typed(arr, index, type) ((type *)da_get((arr), (index)))

#endif
