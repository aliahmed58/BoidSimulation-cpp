#include "../include/button.h"

Button::Button() {}

Button::Button(int x, int y, int width, int height, std::string text) {
    this->x = x;
    this->y = y;
    this->text = text;
    this->width = width;
    this->height = height;
    this->rect = {x, y, width, height};
}

void Button::render(SDL_Renderer* renderer, int r, int g, int b) {
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderFillRect(renderer, &this->rect);
}

void Button::hover(SDL_Renderer* renderer, int r, int g, int b) {
    if (this->on_mouse()) {
        this->render(renderer, r, g, b);
    }
}

bool Button::on_mouse() {
    int x_pos, y_pos;
    SDL_GetMouseState(&x_pos, &y_pos);

    if (x_pos >= x && x_pos <= x + width && y_pos >= y && y_pos <= y + height) {
        return true;
    }
    return false;
}

bool Button::on_click(SDL_Event e) {
    int x_pos = e.button.x;
    int y_pos = e.button.y;

    if (x_pos >= x && x_pos <= x + width && y_pos >= y && y_pos <= y + height) {
        return true;
    }
    return false;
}