#include "raylib.h"
#include "boid.h"
#include <stdlib.h>
#include "utils.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080 
#define BOIDS 400
#define SIMULATION_SPEED 25

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Boids");
    Boids boids = {
        .items = malloc(sizeof(Boid)*BOIDS),
        .length = BOIDS,
    };

    for (int i = 0; i < boids.length; ++i) {
        Vector2 position = { random_float(0, SCREEN_WIDTH), random_float(0, SCREEN_HEIGHT) };
        Vector2 velocity = random_unit_vector();
        Vector2 acceleration = (Vector2){0, 0};
        float max_force = random_float(0.5, 2);
        float speed = random_float(2, 6);
        float size = random_float(10, 15);
        Color color = { GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255 };

        Boid boid = boid_create(i, position, velocity, acceleration, max_force, speed, size, color);
        boids.items[i] = boid;
    }

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground((Color){0x13, 0x13, 0x13, 0xff});

        for (int i = 0; i < BOIDS; ++i) {
            boid_flock(&boids.items[i], boids);
            boid_update(&boids.items[i], SCREEN_WIDTH, SCREEN_HEIGHT, SIMULATION_SPEED);
            boid_draw(boids.items[i]);
        }

        DrawFPS(0, 0);
        EndDrawing();
    }

    CloseWindow();
    free(boids.items);

    return 0;
}
