#pragma once
#include "texture.h"
#include "constants.h"
#include "controls.h"
#include <vector>
#include <bits/stdc++.h>
#include <cmath>

/* Class for an individual boid */
class Boid {

public:
    
    /* default ctor */
    Boid();

    /* ctor with x, y coordinates and SDL_Renderer pointer */
    Boid(float x, float y, SDL_Renderer* renderer);

    /* destructor */
    ~Boid();

    /* method that renders the boid on the screen */
    void render();

    /* update method which will be called on every frame to implement rules */
    void update(double deltaTime, std::vector<Boid*> boids, controls& ctrls);
     
    /* operator overloading for checking if 2 boids are equal w.r.t their x,y values */
    bool operator==(const Boid &boid);

private:

    /* method that applies all the rules of the boid algorithm */
    void apply_rules(std::vector<Boid*> boids, controls& ctrls);

    /* method to implement rule no.1 - Separation */
    void seperation(float delta_x, float delta_y);

    /* method to implement rule no.2 - alignment */
    void alignment(float vx_avg, float vy_avg, int n_boids);

    /* method to implement rule no.3 - cohesion */
    void cohesion(float x_avg, float y_avg, int n_boids);

    /* method that limits speed of boid to min and max speed */
    void limit_speed(double deltaTime);

    /* method that updates the x,y coordinate, called in update */
    void move(double deltaTime);

    /* steer method that will give a smooth turn to the boids as they reach the near end of the screens */
    void steer();

    /* calculates direction angle of boids based on velocity x and velocity y */
    void calc_angle();

    SDL_Renderer* renderer;
    Texture* texutre;
    float x;
    float y;
    float vx;
    float vy;
    float angle;
};