#include "texture.h"
#include "constants.h"
#include <vector>
#include <bits/stdc++.h>
#include <cmath>

class Boid {

public:
    Boid();
    Boid(float x, float y, SDL_Renderer* renderer);
    ~Boid();

    void render();
    void update(double deltaTime, std::vector<Boid*> boids);
     
    bool operator==(const Boid &boid);

private:

    void apply_rules(std::vector<Boid*> boids);
    void seperation(float delta_x, float delta_y);
    void alignment(float vx_avg, float vy_avg, int n_boids);
    void cohesion(float x_avg, float y_avg, int n_boids);
    void limit_speed(double deltaTime);
    void move(double deltaTime);
    void steer();
    void calc_angle();

    SDL_Renderer* renderer;
    Texture* texutre;
    float x;
    float y;
    float vx;
    float vy;
    float angle;
};