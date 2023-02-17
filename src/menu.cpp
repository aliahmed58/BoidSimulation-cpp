#include "../include/menu.h"
#include <stdio.h>

Menu::Menu() {
    
}

Menu::Menu(SDL_Renderer* renderer) {
    this->alignment = Button(10, 10, 100, 30, "Alignment");
    this->separation = Button(120, 10, 100, 30, "Separation");
    this->cohesion = Button(230, 10, 100, 30, "Cohesion");
    this->ctrls = controls();
    this->font = new Font("./res/font.ttf", renderer, 15); 
}

Menu::~Menu() {
    delete font;
}

void Menu::render(SDL_Renderer* renderer) {

    

    if (ctrls.alignment) {
        this->alignment.render(renderer, 0, 200, 0);
        this->alignment.hover(renderer, 200, 0, 0);
    }
    else { 
        this->alignment.render(renderer, 200, 0, 0);
        this->alignment.hover(renderer, 0, 200, 0);
    }
    
    if (ctrls.seperation) {
        this->separation.render(renderer, 0, 200, 0);
        this->separation.hover(renderer, 200, 0, 0);
    }
    else {
        this->separation.render(renderer, 200, 0, 0);
        this->separation.hover(renderer, 0, 200, 0);
    }
    
    if (ctrls.cohesion) {
        this->cohesion.render(renderer, 0, 200, 0);
        this->cohesion.hover(renderer, 200, 0, 0);
    }
    else {
        this->cohesion.render(renderer, 200, 0, 0);
        this->cohesion.hover(renderer, 0, 200, 0);
    }

    SDL_Color white = {255,255,255};
    this->font->render(alignment.x + 15, alignment.y + 4, alignment.text, white);
    this->font->render(separation.x + 15, separation.y + 4, separation.text, white);
    this->font->render(cohesion.x + 20, cohesion.y + 4, cohesion.text, white);

    
}

void Menu::handle_updates(SDL_Event e) {
    if (this->alignment.on_click(e)) {
        ctrls.alignment = !ctrls.alignment;
    }

    if (this->cohesion.on_click(e)) {
        ctrls.cohesion = !ctrls.cohesion;
    }
    
    if (this->separation.on_click(e)) {
        ctrls.seperation = !ctrls.seperation;
    }
}

controls& Menu::get_controls() {
    return this->ctrls;
}