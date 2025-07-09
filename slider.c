#include "slider.h"

Slider slider_create(char *title, Rectangle rect, Color color,  float min_value, float max_value, float init_value, int font_size, int margin, int padding) {
    Slider slider = {
        .title = title,
        .rect = rect,
        .color = color,
        .min_value = min_value,
        .max_value = max_value,
        .cur_value = init_value,
        .font_size = font_size,
        .margin = margin,
        .padding = padding,
        .knob_rect = {rect.x, rect.y, 40, rect.height},
    };
    float t = (init_value - min_value) / (max_value - min_value);
    slider.knob_rect.x = rect.x + t * (rect.width - slider.knob_rect.width);

    return slider;
}

static Rectangle apply_margin(Rectangle rect, int margin) {
    return (Rectangle){
        rect.x + margin,
        rect.y + margin,
        rect.width, rect.height
    };
}

static Rectangle apply_padding(Rectangle rect, int padding) {
    return (Rectangle){
        rect.x + padding,
        rect.y + padding,
        rect.width - padding * 2,
        rect.height - padding * 2,
    };
}

void slider_draw(Slider slider) {
    slider.rect = apply_margin(slider.rect, slider.margin);
    slider.knob_rect = apply_margin(slider.knob_rect, slider.margin);
    slider.knob_rect = apply_padding(slider.knob_rect, slider.padding);
    
    DrawRectangleRec(slider.knob_rect, slider.color);
    slider.color.a /= 2;
    DrawRectangleRec(slider.rect, slider.color);

    char cur_value_string[10];
    sprintf(cur_value_string, "%.2f", slider.cur_value);

    DrawText(cur_value_string, slider.rect.x + slider.rect.width + slider.margin, slider.rect.y + (slider.rect.height - slider.font_size) / 2, slider.font_size, WHITE);
    DrawText(slider.title, slider.rect.x, slider.rect.y - slider.font_size, slider.font_size, WHITE);
}

void slider_update(Slider *slider) {
    Vector2 mouse_pos = GetMousePosition();
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
        CheckCollisionPointRec(mouse_pos, apply_margin(slider->rect, slider->margin))) {
        slider->dragging = true;
    }

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        slider->dragging = false;
    }

    if (slider->dragging) {
        slider->knob_rect.x = mouse_pos.x - slider->margin - slider->knob_rect.width * 0.5; ;
        if (slider->knob_rect.x < slider->rect.x) {
            slider->knob_rect.x = slider-> rect.x;
        }
        if (slider->knob_rect.x > slider->rect.x + slider->rect.width - slider->knob_rect.width) {
            slider->knob_rect.x = slider->rect.x + slider->rect.width - slider->knob_rect.width;
        }

        float t = (slider->knob_rect.x - slider->rect.x) / (slider->rect.width - slider->knob_rect.width);
        slider->cur_value = slider->min_value + t * (slider->max_value - slider->min_value);;
    }
}
