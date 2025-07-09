#include <stdlib.h>
#include "raylib.h"
#include "boid.h"
#include "utils.h"
#include "slider.h"
#include "quadtree.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080 
#define BOIDS 4096
#define SIMULATION_SPEED 25

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Boids");

    Boid *boids = malloc(sizeof(Boid)*BOIDS);

    for (int i = 0; i < BOIDS; ++i) {
        Vector2 position = { random_float(0, SCREEN_WIDTH), random_float(0, SCREEN_HEIGHT) };
        Vector2 velocity = random_unit_vector();
        Vector2 acceleration = (Vector2){0, 0};
        float max_force = random_float(0.5, 2);
        float speed = random_float(2, 6);
        float size = random_float(6, 10);
        Color color = { GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255 };

        boids[i] = boid_create(i, position, velocity, acceleration, max_force, speed, size, color);
    }
    
    Slider alignment = slider_create("Alignment: ", (Rectangle){0, SCREEN_HEIGHT*0.7, 500, 50}, RED, -1.0, 2.0, 1.0, 25, 25, 4);
    Slider cohesion = slider_create("Cohesion: ", (Rectangle){0, alignment.rect.y + alignment.rect.height*1.5, 500, 50}, GREEN, -1.0, 2.0, 1.0, 25, 25, 4);
    Slider separation = slider_create("Separation: ", (Rectangle){0, cohesion.rect.y + cohesion.rect.height*1.5, 500, 50}, BLUE, -1.0, 2.0, 1.0, 25, 25, 4);
    Slider view_radius= slider_create("View radius: ", (Rectangle){0, separation.rect.y + separation.rect.height*1.5, 500, 50}, WHITE, 0.0, 500.0, 100.0, 25, 25, 4);

    while (!WindowShouldClose())
    {
        Quadtree *quadtree = quadtree_create((Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT}, 4);
        for (int i = 0; i < BOIDS; ++i) {
            quadtree_insert(quadtree, &boids[i]);
        }

        BeginDrawing();
        ClearBackground((Color){0x13, 0x13, 0x13, 0xff});

        for (int i = 0; i < BOIDS; ++i) {
            Rectangle range = {
                boids[i].position.x - view_radius.cur_value / 2,
                boids[i].position.y - view_radius.cur_value / 2,
                view_radius.cur_value,
                view_radius.cur_value
            };

            DA nearby_boids;
            da_init(&nearby_boids, sizeof(Boid), 16);

            quadtree_query(quadtree, range, &nearby_boids);

            boid_flock(&boids[i], &nearby_boids, alignment.cur_value, cohesion.cur_value, separation.cur_value, view_radius.cur_value);

            da_free(&nearby_boids);
        }
        quadtree_show(quadtree, WHITE);

        for (int i = 0; i < BOIDS; ++i) {
            boid_update(&boids[i], SCREEN_WIDTH, SCREEN_HEIGHT, SIMULATION_SPEED);
            boid_draw(boids[i]);
        }

        slider_update(&alignment);
        slider_draw(alignment);

        slider_update(&cohesion);
        slider_draw(cohesion);

        slider_update(&separation);
        slider_draw(separation);

        slider_update(&view_radius);
        slider_draw(view_radius);

        DrawFPS(0, 0);
        EndDrawing();

        quadtree_free(quadtree);
    }

    CloseWindow();
    free(boids);

    return 0;
}
