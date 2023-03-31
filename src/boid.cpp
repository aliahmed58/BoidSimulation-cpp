#include "../include/boid.h"

/* gives a random float between 0 and 1 */
float randomFloat() {
    return (float)(rand()) / (float)(RAND_MAX);
}

/* default ctor */
Boid::Boid() {}

/* initializes the boid with x,y and its texture and assigns random velocities (x, y) */
Boid::Boid(float x, float y, SDL_Renderer* renderer, Texture* texture) {
    this->renderer = renderer;
    this->texutre = texture;
    this->x = x;
    this->y = y;
    vx = (randomFloat() - 0.5) * MIN_SPEED;
    vy = (randomFloat() - 0.5) * MIN_SPEED;
}

/* deallocates the boid and its texture */
Boid::~Boid() {
    this->texutre->free();
}

/* overriding equals operator to check equality of boids with x,y coordinates */
bool Boid::operator==(const Boid &boid) {
    return boid.x == this->x && boid.y == this->y;
} 

/* renders the boid on screen */
void Boid::render() {
    int height = this->texutre->getHeight();
    int width = this->texutre->getWidth();
    SDL_Rect src = {0, 0, width, height};
    SDL_Rect dst = {(int) x, (int) y, width, height};
    this->texutre->renderCopyEx(&src, &dst, nullptr, angle);
}

/* calculating the angle of direction based on vx and vy */
void Boid::calc_angle() {
    
    float radAngle = atan2(vy, vx);

    /* converting angle to degrees */
    angle = radAngle * (180 / M_PI);

    /* adding 90 to align with SDL2's angle */
    angle += 90;
}

/* update method called on every frame */
void Boid::update(double deltaTime, std::vector<Boid*> boids, controls& ctrls) {

    /* calculate and set angle of the boid */
    this->calc_angle();

    /* apply rules based on the controls given, if they're true */
    this->apply_rules(boids, ctrls);

    /* limits speed if the boids get too fast */
    this->limit_speed(deltaTime);

    /* steers if the boid reaches end of screen */
    this->steer();

    /* updates x, y of the boid */
    this->move(deltaTime);
}

/* updates the x,y coordinate of the boid */
void Boid::move(double deltaTime) {
    x += vx * deltaTime / 10;
    y += vy * deltaTime / 10;
}

void Boid::steer() {

    /* update the vx and vy based on the boid reaching an edge and give it a smooth turning effect */
    if (x < LEFT_MARGIN) vx += TURN_FACTOR;
    if (x > RIGHT_MARGIN) vx -= TURN_FACTOR;
    if (y < TOP_MARGIN) vy += TURN_FACTOR;
    if (y > BOTTOM_MARGIN) vy -= TURN_FACTOR;
}

/* limits the speed of the boid to min and max */
void Boid::limit_speed(double deltaTime) {

    /* calculate the speed or the resultant vector from vx and vy using speed^2 = vx^2 + vy^2 */
    float speed = sqrt(vx * vx + vy * vy) * deltaTime / 10;

    /* if the speed is greater than max speed adjust it by the MAX SPEED */
    if (speed > MAX_SPEED) {
        vx = (vx / speed) * MAX_SPEED;
        vy = (vy / speed) * MAX_SPEED;
    }

    /* if the speed is less than the min speed, adjust it by the MIN SPEED */
    if (speed < MIN_SPEED) {
        vx = (vx / speed) * MIN_SPEED;
        vy = (vy / speed) * MIN_SPEED;
    }
}

/* Applies all the rules of boid based on the controls struct reference passed
 * If the bool in controls are set to true, the rule is applied */
void Boid::apply_rules(std::vector<Boid*> boids, controls& ctrls) {

    /* initialize difference in position, avg velocities, average position and total no. of boids as  0 */
    float delta_x = 0, delta_y = 0;
    float vx_avg = 0, vy_avg = 0;
    float x_avg = 0, y_avg = 0;
    int n_boids = 0;

    /* loop over every boid in the vector */
    for (long unsigned int i = 0; i < boids.size(); i ++) {
        
        /* if the boid is being compared to itself, skip */
        if (this == boids.at(i)) continue;

        /* get the pointer to boid at ith index */
        Boid* boid = boids.at(i);

        /* calculate the euclidean distance between self and neighboring boid at ith index */
        float distance = sqrt(pow((boid->x - this->x), 2) + pow((boid->y - this->y), 2));

        /* if the distance is within the protected range */
        if (distance <= PROTECTED_RANGE) {
            
            /* add the difference of position to delta_x and delta_y  */
            delta_x += this->x - boid->x;
            delta_y += this->y - boid->y;
        }

        /* if the distance is also within the visual range */
        if (distance < VISUAL_RANGE) {
            
            /* sum up the velocities of the neighbors */
            vx_avg += boid->vx;
            vy_avg += boid->vy;

            /* sum up the position of the neighbors */
            x_avg += boid->x;
            y_avg += boid->y;

            /* increment the no. of neighboring boids */
            n_boids ++;
        }
    }

    /* if the neighboring boids were found within that range are more than 0 */
    if (n_boids > 0 ) {

        /* if the alignment bool is set to true in controls */
        if (ctrls.alignment) 
            /* apply alignment rule */
            this->alignment(vx_avg, vy_avg, n_boids);
        
        /* if the cohesion bool is set to true in controls */
        if (ctrls.cohesion)
            /* apply cohesion rule */
            this->cohesion(x_avg, y_avg, n_boids);
    }

    /* if the separation rule is set to true in controls */
    if (ctrls.seperation)
        /* apply separation */
        this->seperation(delta_x, delta_y);
}

/* Rule 1. Separation
 * The boids attempt to run away from each other, if they get close in a certain range from other boid
 * they will steer away from other boids */
void Boid::seperation(float delta_x, float delta_y) {

    /* After all boids have been looped over, adjust the current boids velocity's x and y components */
    this->vx += delta_x * SEPERATION_FACTOR;
    this->vy += delta_y * SEPERATION_FACTOR;
}

/* Rule 2. Alignment
 * The boids attempt to align with the velocities of neighboring boids in its visible range
 * It is done by averaging out the velocities of all the boids in given range */
void Boid::alignment(float vx_avg, float vy_avg, int n_boid) {

    /* after looping over all boids in visual range, calculate the avg vx and vy */
    vx_avg /= n_boid;
    vy_avg /= n_boid;

    /* update the velocity of the boid based on the average in visual range */
    this->vx += (vx_avg - this->vx) * ALIGNMENT_FACTOR;
    this->vy += (vy_avg - this->vy) * ALIGNMENT_FACTOR;
}

/* Rule 3. Cohesion
 * The boid moves slowly towards the centre of mass of other boids in the its visible range
 * The x, y position is averaged out of boids in the visible range and then the boids velocity
 * is adjusted accordingly */
void Boid::cohesion(float x_avg, float y_avg, int n_boids) {

    /* after looping over all boids in visual range, calculate the avg x and y position */
    x_avg /= n_boids;
    y_avg /= n_boids;
    
    /* update the velocity of the boid based on the average in visual range */
    this->vx += (x_avg - this->x) * COHESION_FACTOR;
    this->vy += (y_avg - this->y) * COHESION_FACTOR;
}
