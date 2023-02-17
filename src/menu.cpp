#include "../include/menu.h"
#include <stdio.h>

Menu::Menu() {
    this->alignment = Button(10, 10, 100, 30, "Alignment");
    this->separation = Button(120, 10, 100, 30, "Separation");
    this->cohesion = Button(230, 10, 100, 30, "Cohesion");
}

void Menu::render(SDL_Renderer* renderer) {
    
    if (alignment_bool)
        this->alignment.render(renderer, 0, 200, 0);
    else 
        this->alignment.render(renderer, 200, 0, 0);
    
    if (seperation_bool)
        this->separation.render(renderer, 0, 200, 0);
    else
        this->separation.render(renderer, 200, 0, 0);
    
    if (cohesion_bool)
        this->cohesion.render(renderer, 0, 200, 0);
    else
        this->cohesion.render(renderer, 200, 0, 0);

    this->alignment.hover(renderer);
    this->separation.hover(renderer);
    this->cohesion.hover(renderer);

    
}

void Menu::handle_updates(SDL_Event e) {
    if (this->alignment.on_click(e)) {
        alignment_bool = !alignment_bool;
    }

    if (this->cohesion.on_click(e)) {
        cohesion_bool = !cohesion_bool;
    }
    
    if (this->separation.on_click(e)) {
        seperation_bool = !seperation_bool;
    }
}