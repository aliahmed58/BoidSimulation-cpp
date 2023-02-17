#pragma once
#include <SDL.h>
#include <string>

class Button {

public:
    Button();
    Button(int x, int y, int width, int height, std::string text);
    void render(SDL_Renderer* renderer, int r, int g, int b);
    void hover(SDL_Renderer* renderer, int r, int g, int b);
    bool on_mouse();
    bool on_click(SDL_Event e);
    int x;
    int y;
    int width;
    int height;
    std::string text;

private:
    SDL_Rect rect;
};