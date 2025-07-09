#include "dynamic_array.h"

void da_init(DA *a, size_t elem_size, size_t init_size) {
    a->data = malloc(init_size * elem_size);
    a->used = 0;
    a->size = init_size;
    a->elem_size = elem_size;
}

void da_push(DA *a, void *element) {
    if (a->used == a->size) {
        a->size *= 2;
        a->data = realloc(a->data, a->size * a->elem_size);
    }
    void *target = (char *)a->data + (a->used * a->elem_size);
    memcpy(target, element, a->elem_size);
    a->used++;
}

void *da_get(DA *a, size_t index) {
    if (index >= a->used) return NULL;
    return (char *)a->data + (index * a->elem_size);
}

void da_free(DA *a) {
    free(a->data);
    a->data = NULL;
    a->used = a->size = a->elem_size = 0;
}
