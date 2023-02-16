#include "../include/boid.h"

float randomFloat() {
    return (float)(rand()) / (float)(RAND_MAX);
}

Boid::Boid() {}

Boid::Boid(float x, float y, SDL_Renderer* renderer) {
    this->renderer = renderer;
    this->texutre = new Texture("./res/boid.png", renderer);
    this->x = x;
    this->y = y;
    vx = (randomFloat() - 0.5) * MIN_SPEED;
    vy = (randomFloat() - 0.5) * MIN_SPEED;
}

Boid::~Boid() {
    this->texutre->free();
}

bool Boid::operator==(const Boid &boid) {
    return boid.x == this->x && boid.y == this->y;
} 

void Boid::render() {
    int height = this->texutre->getHeight();
    int width = this->texutre->getWidth();
    SDL_Rect src = {0, 0, width, height};
    SDL_Rect dst = {(int) x, (int) y, width, height};
    this->texutre->renderCopyEx(&src, &dst, nullptr, angle);
}

void Boid::calc_angle() {
    float radAngle = atan2(vy, vx);
    angle = radAngle * (180 / M_PI);
    angle += 90;
}

void Boid::update(double deltaTime, std::vector<Boid*> boids) {

    this->calc_angle();

    this->apply_rules(boids);

    this->limit_speed(deltaTime);

    this->steer();

    this->move(deltaTime);
}

void Boid::move(double deltaTime) {
    x += vx * deltaTime / 10;
    y += vy * deltaTime / 10;
}

void Boid::steer() {
    if (x < LEFT_MARGIN) vx += TURN_FACTOR;
    if (x > RIGHT_MARGIN) vx -= TURN_FACTOR;
    if (y < TOP_MARGIN) vy += TURN_FACTOR;
    if (y > BOTTOM_MARGIN) vy -= TURN_FACTOR;
}

void Boid::limit_speed(double deltaTime) {
    float speed = sqrt(vx * vx + vy * vy) * deltaTime / 10;

    if (speed > MAX_SPEED) {
        vx = (vx / speed) * MAX_SPEED;
        vy = (vy / speed) * MAX_SPEED;
    }
    if (speed < MIN_SPEED) {
        vx = (vx / speed) * MIN_SPEED;
        vy = (vy / speed) * MIN_SPEED;
    }
}

void Boid::apply_rules(std::vector<Boid*> boids) {

    float delta_x = 0, delta_y = 0;
    float vx_avg = 0, vy_avg = 0;
    float x_avg = 0, y_avg = 0;
    int n_boids = 0;

    for (int i = 0; i < boids.size(); i ++) {
        
        if (this == boids.at(i)) continue;

        Boid* boid = boids.at(i);

        float distance = sqrt(pow((boid->x - this->x), 2) + pow((boid->y - this->y), 2));

        if (distance < PROTECTED_RANGE) {

            delta_x += this->x - boid->x;
            delta_y += this->y - boid->y;
        }

        if (distance < VISUAL_RANGE) {
            vx_avg += boid->vx;
            vy_avg += boid->vy;

            x_avg += boid->x;
            y_avg += boid->y;

            n_boids ++;
        }
    }

    if (n_boids > 0 ) {
        this->alignment(vx_avg, vy_avg, n_boids);
        this->cohesion(x_avg, y_avg, n_boids);
    }

    this->seperation(delta_x, delta_y);
}

void Boid::seperation(float delta_x, float delta_y) {
    this->vx += delta_x * SEPERATION_FACTOR;
    this->vy += delta_y * SEPERATION_FACTOR;
}

void Boid::alignment(float vx_avg, float vy_avg, int n_boid) {
    vx_avg /= n_boid;
    vy_avg /= n_boid;

    this->vx += (vx_avg - this->vx) * ALIGNMENT_FACTOR;
    this->vy += (vy_avg - this->vy) * ALIGNMENT_FACTOR;
}

void Boid::cohesion(float x_avg, float y_avg, int n_boids) {
    x_avg /= n_boids;
    y_avg /= n_boids;

    this->vx += (x_avg - this->x) * COHESION_FACTOR;
    this->vy += (y_avg - this->y) * COHESION_FACTOR;
}