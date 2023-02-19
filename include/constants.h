/* Constants header file to store all the constants needed throughout code */
#pragma once
#include <string>

/* Window dimensions and title constants */
const int SCREEN_HEIGHT = 750;
const int SCREEN_WIDTH = 1300;
const std::string WINDOW_TITLE = "Boids - Flocking Behaviour Simulation";

/* No. of initial boids spawned when program runs */
const int INITIAL_BOIDS = 20;

/* Margins at which the boids will start steering - take a smooth turn */
const int LEFT_MARGIN = 100;
const int RIGHT_MARGIN = SCREEN_WIDTH - LEFT_MARGIN;
const int TOP_MARGIN = 150;
const int BOTTOM_MARGIN = SCREEN_HEIGHT - TOP_MARGIN;

/* Minimum and maximum speed of boids */
const int MIN_SPEED = 3;
const int MAX_SPEED = 6;

/* Turn factor by which the boids will take a turn when reaching the edges */
const float TURN_FACTOR = 0.3;

/* The range at which every boid will move away from other boid within this range */
const int PROTECTED_RANGE = 30;

/* The range at which the boids can see, impelemnt alignment and cohesion */
const int VISUAL_RANGE = 90;

/* Factors of the three rules */
const float ALIGNMENT_FACTOR = 0.09;
const float COHESION_FACTOR = 0.0005;
const float SEPERATION_FACTOR = 0.05;