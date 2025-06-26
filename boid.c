#include "raylib.h"
#include "raymath.h"
#include "boid.h"
#include "utils.h"

Boid boid_create(int id, Vector2 position, Vector2 velocity, Vector2 acceleration, float max_force, float speed, int size, Color color) {
    Boid boid = {
        .id = id,
        .position = position,
        .velocity = velocity,
        .acceleration = acceleration,
        .max_force = max_force,
        .speed = speed,
        .size = size,
        .color = color,
    };
    return boid;
}

void boid_draw(Boid boid) {
    DrawCircleV(boid.position, boid.size, boid.color);
    DrawCircleV(Vector2Add(boid.position, vector_set_length(boid.velocity, boid.size*0.5)), boid.size/2, WHITE);
}

void boid_handle_edges(Boid *boid, int screen_width, int screen_height) {
    if (boid->position.x > screen_width) {
        boid->position.x = 0;
    } else if (boid->position.x < 0) {
        boid->position.x = screen_width;
    }

    if (boid->position.y > screen_height) {
        boid->position.y = 0;
    } else if (boid->position.y < 0) {
        boid->position.y = screen_height;
    }
}

void boid_update(Boid *boid, int screen_width, int screen_height, int simulation_speed) {

    boid_handle_edges(boid, screen_width, screen_height);
    boid->position = Vector2Add(boid->position, Vector2Scale(boid->velocity, GetFrameTime()*simulation_speed));
    boid->velocity = Vector2Add(boid->velocity, Vector2Scale(boid->acceleration, GetFrameTime()*simulation_speed));
    boid->velocity = vector_limit(boid->velocity, boid->speed);
    boid->acceleration = Vector2Zero();
}

void boid_flock(Boid *target, Boids boids) {
    Vector2 alignment = Vector2Zero();
    Vector2 cohesion = Vector2Zero();
    Vector2 separation = Vector2Zero();

    int view_radius = 100;
    int total = 0;

    for (int i = 0; i < boids.length; ++i) {
        Boid other = boids.items[i];
        float d = Vector2Distance(target->position, other.position);
        if (target->id != other.id && d < view_radius) {
            Vector2 diff = Vector2Subtract(target->position, other.position);
            if (d > 0) diff = Vector2Scale(diff, 1/d);

            separation = Vector2Add(separation, diff);
            alignment = Vector2Add(alignment, other.velocity);
            cohesion = Vector2Add(cohesion, other.position);

            total++;
        }
    }
    if (total > 0) {
        alignment = (Vector2){alignment.x/total, alignment.y/total};
        cohesion = (Vector2){cohesion.x/total, cohesion.y/total};
        cohesion = Vector2Subtract(cohesion, target->position);
        separation = (Vector2){separation.x/total, separation.y/total};

        alignment = vector_set_length(alignment, target->speed);
        cohesion = vector_set_length(cohesion, target->speed);
        separation = vector_set_length(separation, target->speed);

        alignment = Vector2Subtract(alignment, target->velocity);
        cohesion = Vector2Subtract(cohesion, target->velocity);
        separation = Vector2Subtract(separation, target->velocity);

        alignment = vector_limit(alignment, target->max_force);
        cohesion = vector_limit(cohesion, target->max_force);
        separation = vector_limit(separation, target->max_force);
    }

    // scale one of the forces here
    // separation = Vector2Scale(separation, 1.5);
    // cohesion = Vector2Scale(cohesion, 1.5);
    alignment = Vector2Scale(alignment, 1.5);

    target->acceleration = Vector2Add(target->acceleration, alignment);
    target->acceleration = Vector2Add(target->acceleration, cohesion);
    target->acceleration = Vector2Add(target->acceleration, separation);
}
