#pragma once
#include <SDL.h>
#include <string>

/* class that is used to create UI buttons */
class Button {

public:
    Button();
    
    /* ctor initalizing button properties */
    Button(int x, int y, int width, int height, std::string text);

    /* render method that will render the button on screen */
    void render(SDL_Renderer* renderer, int r, int g, int b);

    /* method that will render button when hovered upon */
    void hover(SDL_Renderer* renderer, int r, int g, int b);

    /* method that returns true if button is hovered */
    bool on_mouse();

    /* method that returns true if button is clicked */
    bool on_click(SDL_Event e);

    /* properties of button */
    int x;
    int y;
    int width;
    int height;
    std::string text;

private:
    SDL_Rect rect;
};