#pragma once
#include <SDL.h>
#include "constants.h"
#include "button.h"

class Menu {

public:
    Menu();
    void render(SDL_Renderer* renderer);   
    void handle_updates(SDL_Event e); 

private:
    Button separation;
    Button alignment;
    Button cohesion;
};