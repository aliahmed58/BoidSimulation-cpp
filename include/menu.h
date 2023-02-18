#pragma once
#include <SDL.h>
#include <iostream>
#include <vector>
#include "boid.h"
#include "controls.h"
#include "texture.h"
#include "button.h"
#include "font.h"

class Menu {

public:
    Menu();
    Menu(SDL_Renderer* renderer);
    ~Menu();
    void render(SDL_Renderer* renderer);   
    void handle_updates(SDL_Event e, std::vector<Boid*>& boids); 
    controls &get_controls();

private:
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
};