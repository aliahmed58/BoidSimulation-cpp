#pragma once
#include <SDL.h>
#include <iostream>
#include "controls.h"
#include "button.h"
#include "font.h"

class Menu {

public:
    Menu();
    Menu(SDL_Renderer* renderer);
    ~Menu();
    void render(SDL_Renderer* renderer);   
    void handle_updates(SDL_Event e); 
    controls &get_controls();

private:
    Button separation;
    Button alignment;
    Button cohesion;
    controls ctrls;
    Font* font;
};