#ifndef QUADTREE_H
#define QUADTREE_H

#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>

#include "dynamic_array.h"
#include "raylib.h"
#include "boid.h"

typedef struct Quadtree {
    Rectangle boundary;
    int capacity;

    DA boids;
    bool divided;

    struct Quadtree *ne;
    struct Quadtree *nw;
    struct Quadtree *se;
    struct Quadtree *sw;
} Quadtree;

Quadtree *quadtree_create(Rectangle boundary, int capacity);
void quadtree_free(Quadtree *qt);
void quadtree_show(Quadtree *qt, Color color);

bool quadtree_insert(Quadtree *qt, Boid *boid);
void quadtree_query(Quadtree *qt, Rectangle range, DA *found);

#endif

