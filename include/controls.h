#pragma once

struct controls {
    bool alignment;
    bool seperation;
    bool cohesion;
    int boid_count;

    controls() {
        alignment = false;
        seperation = false;
        cohesion = false;
        boid_count = 1;
    }
};