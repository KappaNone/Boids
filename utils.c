#include "utils.h"
#include "raylib.h"
#include "raymath.h"

float random_float(float from, float to) {
    int steps = 10000;
    return from + ((float)GetRandomValue(0, steps) / steps) * (to - from);
}

Vector2 random_unit_vector(void) {
    float angle = GetRandomValue(0, 360) * DEG2RAD; 
    return (Vector2){ cosf(angle), sinf(angle) };
}

Vector2 vector_set_length(Vector2 v, float length) {
    return Vector2Scale(Vector2Normalize(v), length);
}

Vector2 vector_limit(Vector2 v, float length) {
    if (Vector2Length(v) > length) {
        return vector_set_length(v, length);
    }
    return v;
}
