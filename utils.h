#ifndef UTILS_H
#define UTILS_H
#include "raylib.h"

// typedef struct List {
//     int length;
//     void *items;
// } List;

float random_float(float from, float to);

Vector2 random_unit_vector(void);

Vector2 vector_set_length(Vector2 v, float length);

Vector2 vector_limit(Vector2 v, float length);

#endif
