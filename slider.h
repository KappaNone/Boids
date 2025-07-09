#ifndef SLIDER_H
#define SLIDER_H

#include "raylib.h"
#include <stdio.h>

typedef struct Slider {
    char *title;
    Rectangle rect;
    Color color;
    float min_value;
    float max_value;
    float cur_value;
    int font_size;
    Rectangle knob_rect;
    int margin;
    int padding;
    bool dragging;
} Slider;

Slider slider_create(char *title, Rectangle rect, Color color, float min_value, float max_value, float init_value, int font_size, int margin, int padding);

void slider_draw(Slider);
void slider_update(Slider*);

#endif
