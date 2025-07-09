#include "quadtree.h"

Quadtree *quadtree_create(Rectangle boundary, int capacity) {
    Quadtree *qt = malloc(sizeof(Quadtree));
    qt->boundary = boundary;
    qt->capacity = capacity;
    qt->divided = false;
    qt->ne = qt->nw = qt->se = qt->sw = NULL;

    da_init(&qt->boids, sizeof(Boid), capacity);
    return qt;
}

void quadtree_subdivide(Quadtree *qt) {
    float x = qt->boundary.x;
    float y = qt->boundary.y;
    float w = qt->boundary.width / 2;
    float h = qt->boundary.height / 2;

    qt->ne = quadtree_create((Rectangle){x + w, y, w, h}, qt->capacity);
    qt->nw = quadtree_create((Rectangle){x, y, w, h}, qt->capacity);
    qt->se = quadtree_create((Rectangle){x + w, y + h, w, h}, qt->capacity);
    qt->sw = quadtree_create((Rectangle){x, y + h, w, h}, qt->capacity);

    qt->divided = true;
}

bool quadtree_insert(Quadtree *qt, Boid *boid) {
    if (!CheckCollisionPointRec(boid->position, qt->boundary))
        return false;

    if (qt->boids.used < (size_t)qt->capacity) {
        da_push(&qt->boids, boid);
        return true;
    }

    if (!qt->divided)
        quadtree_subdivide(qt);

    return quadtree_insert(qt->ne, boid) ||
        quadtree_insert(qt->nw, boid) ||
        quadtree_insert(qt->se, boid) ||
        quadtree_insert(qt->sw, boid);
}

void quadtree_query(Quadtree *qt, Rectangle range, DA *found) {
    if (!CheckCollisionRecs(qt->boundary, range))
        return;

    for (size_t i = 0; i < qt->boids.used; i++) {
        Boid *p = da_get_typed(&qt->boids, i, Boid);
        if (CheckCollisionPointRec(p->position, range)) {
            da_push(found, p);
        }
    }

    if (qt->divided) {
        quadtree_query(qt->ne, range, found);
        quadtree_query(qt->nw, range, found);
        quadtree_query(qt->se, range, found);
        quadtree_query(qt->sw, range, found);
    }
}

void quadtree_show(Quadtree *qt, Color color) {
    if (!qt) return;

    DrawRectangleLines((int)qt->boundary.x, (int)qt->boundary.y,
            (int)qt->boundary.width, (int)qt->boundary.height,
            color);

    if (qt->divided) {
        quadtree_show(qt->ne, color);
        quadtree_show(qt->nw, color);
        quadtree_show(qt->se, color);
        quadtree_show(qt->sw, color);
    }
}

void quadtree_free(Quadtree *qt) {
    if (qt->divided) {
        quadtree_free(qt->ne);
        quadtree_free(qt->nw);
        quadtree_free(qt->se);
        quadtree_free(qt->sw);
    }
    da_free(&qt->boids);
    free(qt);
}

