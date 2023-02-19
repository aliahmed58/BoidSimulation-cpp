#include "../include/menu.h"
#include <stdio.h>

Menu::Menu() {
    
}

/* initializes menu with all the UI elements and textures needed */
Menu::Menu(SDL_Renderer* renderer) {

    /* Rules button to turn them on or off */
    this->alignment = Button(10, 10, 100, 30, "Alignment");
    this->separation = Button(120, 10, 100, 30, "Separation");
    this->cohesion = Button(230, 10, 100, 30, "Cohesion");
    this->kill_boid = Button(SCREEN_WIDTH - 350, 10, 100, 30, "Kill boid");

    /* a controls struct variable */
    this->ctrls = controls();

    /* text textures to display pre rendered text */
    this->separation_text = new Texture("./res/separation.png", renderer);
    this->alignment_text = new Texture("./res/alignment.png", renderer);
    this->cohesion_text = new Texture("./res/cohesion.png", renderer);
    this->kill_text = new Texture("./res/kill.png", renderer);
    this->ins = new Texture("./res/ins.png", renderer);

    /* font object to render font and no. of boids */
    this->font = new Font("./res/font.ttf", renderer, 25);
}

/* deallocate all textures on delete */
Menu::~Menu() {
    delete font;
    this->separation_text->free();
    this->alignment_text->free();
    this->cohesion_text->free();
    this->kill_text->free();
    this->ins->free();
}

/* renders the whole menu  */
void Menu::render(SDL_Renderer* renderer) {

    /* If the rules are activated, render their buttons with green background
     * if they're disabled, render their buttons with red background */

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

    /* render the kill boid button and apply hover to all buttons with a different background */
    this->kill_boid.render(renderer, 9, 125, 192);
    this->kill_boid.hover(renderer, 200, 0, 0);
    this->separation.hover(renderer, 24, 24, 35);
    this->cohesion.hover(renderer, 24, 24, 35);
    this->alignment.hover(renderer, 24, 24, 35);
    
    /* Render all the prerendered text textuures on buttons */
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

    SDL_Rect src4 = {0, 0, ins->getWidth(), ins->getHeight()};
    SDL_Rect dst4 = {(SCREEN_WIDTH / 2) - 200, 18, ins->getWidth(), ins->getHeight()};
    ins->render(&src4, &dst4);

    /* render the total boid count as font and take the boid count from controls struct */
    SDL_Color black = {0, 0, 0};
    std::string n_boids = "Total boids: " + std::to_string(ctrls.boid_count);
    this->font->render(SCREEN_WIDTH - 220, 10, n_boids, black);    
}


/* handle updates on UI such as mouse click */
void Menu::handle_updates(SDL_Event e, std::vector<Boid*>& boids) {

    /* if any of the rule on off button is clicked, invert the rule boolean and update in controls struct used
     * if it was on, it'll be turned off and vice versa */

    if (this->alignment.on_click(e)) {
        ctrls.alignment = !ctrls.alignment;
    }

    if (this->cohesion.on_click(e)) {
        ctrls.cohesion = !ctrls.cohesion;
    }
    
    if (this->separation.on_click(e)) {
        ctrls.seperation = !ctrls.seperation;
    }

    /* if the kill boid button is clicked */
    if (this->kill_boid.on_click(e)) {

        /* if the boids are more than 0, i.e the at least one boid exists */
        if (boids.size() > 0) {

            /* de allocate that boid on kill boid click */
            delete boids.at(0);

            /* remove from the vector */
            boids.erase(boids.begin());

            /* decrement the total boids count */
            ctrls.boid_count = boids.size();
        }
    }
}

/* get a reference for menu controls to use in the boid class */
controls& Menu::get_controls() {
    return this->ctrls;
}