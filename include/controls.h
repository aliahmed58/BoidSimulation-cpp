#pragma once
#include "constants.h"

/* A struct to hold the controls for UI */
struct controls {

    /* Switches the alignment, cohesion, separation on off */
    bool alignment;
    bool seperation;
    bool cohesion;

    /* to store the total no. of boids */
    int boid_count;

    /* initially everything is off and boid count is set to initial count */
    controls() {
        alignment = false;
        seperation = false;
        cohesion = false;
        boid_count = INITIAL_BOIDS;
    }
};