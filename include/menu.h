#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include "boid.h"
#include "controls.h"
#include "texture.h"
#include "button.h"
#include "font.h"

/* Class that holds all UI elements */
class Menu {

public:
    Menu();
    Menu(SDL_Renderer* renderer);
    ~Menu();

    /* renders the complete menu */
    void render(SDL_Renderer* renderer);   

    /* Handles updates such as mouse clicks on buttons */
    void handle_updates(SDL_Event e, std::vector<Boid*>& boids); 
    controls &get_controls();

private:
    /* All UI elements such as buttons, text textures and font */
    Button separation;
    Button alignment;
    Button cohesion;
    Button kill_boid;
    controls ctrls;
    Font* font;
    Texture* separation_text;
    Texture* kill_text;
    Texture* alignment_text;
    Texture* cohesion_text;
    Texture* ins;
};
