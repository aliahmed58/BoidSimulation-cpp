#include "../include/menu.h"
#include <stdio.h>

Menu::Menu() {
    
}

Menu::Menu(SDL_Renderer* renderer) {
    this->alignment = Button(10, 10, 100, 30, "Alignment");
    this->separation = Button(120, 10, 100, 30, "Separation");
    this->cohesion = Button(230, 10, 100, 30, "Cohesion");
    this->kill_boid = Button(SCREEN_WIDTH - 350, 10, 100, 30, "Kill boid");
    this->ctrls = controls();

    this->separation_text = new Texture("./res/separation.png", renderer);
    this->alignment_text = new Texture("./res/alignment.png", renderer);
    this->cohesion_text = new Texture("./res/cohesion.png", renderer);
    this->kill_text = new Texture("./res/kill.png", renderer);

    this->font = new Font("./res/font.ttf", renderer, 25);
}

Menu::~Menu() {
    delete font;
    this->separation_text->free();
    this->alignment_text->free();
    this->cohesion_text->free();
    this->kill_text->free();
}

void Menu::render(SDL_Renderer* renderer) {

    if (ctrls.alignment) {
        this->alignment.render(renderer, 0, 200, 0);
    }
    else { 
        this->alignment.render(renderer, 200, 0, 0);
    }
    
    if (ctrls.seperation) {
        this->separation.render(renderer, 0, 200, 0);
    }
    else {
        this->separation.render(renderer, 200, 0, 0);
    }
    
    if (ctrls.cohesion) {
        this->cohesion.render(renderer, 0, 200, 0);
    }
    else {
        this->cohesion.render(renderer, 200, 0, 0);
    }

    this->kill_boid.render(renderer, 9, 125, 192);
    this->kill_boid.hover(renderer, 200, 0, 0);
    this->separation.hover(renderer, 24, 24, 35);
    this->cohesion.hover(renderer, 24, 24, 35);
    this->alignment.hover(renderer, 24, 24, 35);
    
    SDL_Rect src ={0, 0, separation_text->getWidth(), separation_text->getHeight()};
    SDL_Rect dst = {separation.x, separation.y, separation_text->getWidth(), separation_text->getHeight()};
    separation_text->render(&src, &dst);

    SDL_Rect src1 = {0, 0, alignment_text->getWidth(), alignment_text->getHeight()};
    SDL_Rect dst1 = {alignment.x, alignment.y, alignment_text->getWidth(), alignment_text->getHeight()};
    alignment_text->render(&src1, &dst1);

    SDL_Rect src2 = {0, 0, cohesion_text->getWidth(), cohesion_text->getHeight()};
    SDL_Rect dst2 = {cohesion.x, cohesion.y, cohesion_text->getWidth(), cohesion_text->getHeight()};
    cohesion_text->render(&src2, &dst2);

    SDL_Rect src3 = {0, 0, kill_text->getWidth(), kill_text->getHeight()};
    SDL_Rect dst3 = {kill_boid.x, kill_boid.y, kill_text->getWidth(), kill_text->getHeight()};
    kill_text->render(&src3, &dst3);

    SDL_Color black = {0, 0, 0};
    std::string n_boids = "Total boids: " + std::to_string(ctrls.boid_count);
    this->font->render(SCREEN_WIDTH - 220, 10, n_boids, black);

    this->font->render((SCREEN_WIDTH / 2) - 200, 10, "Click anywhere to add a boid", black);
    
}

void Menu::handle_updates(SDL_Event e, std::vector<Boid*>& boids) {
    if (this->alignment.on_click(e)) {
        ctrls.alignment = !ctrls.alignment;
    }

    if (this->cohesion.on_click(e)) {
        ctrls.cohesion = !ctrls.cohesion;
    }
    
    if (this->separation.on_click(e)) {
        ctrls.seperation = !ctrls.seperation;
    }

    if (this->kill_boid.on_click(e)) {
        if (boids.size() > 0) {
            delete boids.at(0);
            boids.erase(boids.begin());
            ctrls.boid_count --;
        }
    }
}

controls& Menu::get_controls() {
    return this->ctrls;
}