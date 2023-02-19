#include "../include/button.h"

Button::Button() {}

/* initializes the button with x,y width height and makes a rect for it */
Button::Button(int x, int y, int width, int height, std::string text) {
    this->x = x;
    this->y = y;
    this->text = text;
    this->width = width;
    this->height = height;
    this->rect = {x, y, width, height};
}

/* renders the button given rgb color values */
void Button::render(SDL_Renderer* renderer, int r, int g, int b) {
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderFillRect(renderer, &this->rect);
}

/* if the button is hovered, renders the button with given rgb values */
void Button::hover(SDL_Renderer* renderer, int r, int g, int b) {
    if (this->on_mouse()) {
        this->render(renderer, r, g, b);
    }
}

/* checks if the button is hovered upon */
bool Button::on_mouse() {

    /* get the x,y of mouse */
    int x_pos, y_pos;
    SDL_GetMouseState(&x_pos, &y_pos);

    /* if the x,y are over the button, return true */
    if (x_pos >= x && x_pos <= x + width && y_pos >= y && y_pos <= y + height) {
        return true;
    }
    /* else return false */
    return false;
}

/* returns true if the button is clicked */
bool Button::on_click(SDL_Event e) {

    /* get x,y pos from SDL_Event e on MOUSEBUTTONDOWN */
    int x_pos = e.button.x;
    int y_pos = e.button.y;

    /* if its clicked over the rect, return true */
    if (x_pos >= x && x_pos <= x + width && y_pos >= y && y_pos <= y + height) {
        return true;
    }
    /* else return false */
    return false;
}