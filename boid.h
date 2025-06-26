#ifndef BOID_H
#define BOID_H

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

typedef struct Boids {
    Boid *items;
    int length;
} Boids;

Boid boid_create(int id, Vector2 position, Vector2 velocity, Vector2 acceleration, float max_force, float speed, int size, Color color);
void boid_update(Boid* target, int screen_width, int screen_height, int simulation_speed);
void boid_draw(Boid);
void boid_flock(Boid *target, Boids boids);

#endif
