#ifndef BOID_H
#define BOID_H
#include "utils.h"
typedef struct Boid {
    int id;
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;
    float max_force;
    float speed;
    float size;
    Color color;
} Boid;

Boid boid_create(int id, Vector2 position, Vector2 velocity, Vector2 acceleration, float max_force, float speed, int size, Color color);
void boid_update(Boid* target, int screen_width, int screen_height, int simulation_speed);
void boid_draw(Boid);
void boid_flock(Boid *target, Boid* boids, int boids_len, float alignment_factor, float cohesion_factor, float separation_factor, float view_radius);

#endif
