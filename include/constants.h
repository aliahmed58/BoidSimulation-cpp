#pragma once
#include <string>

const int SCREEN_HEIGHT = 750;
const int SCREEN_WIDTH = 1280;
const std::string WINDOW_TITLE = "Boids - Flocking Behaviour Simulation";

const int LEFT_MARGIN = 100;
const int RIGHT_MARGIN = SCREEN_WIDTH - LEFT_MARGIN;
const int TOP_MARGIN = 100;
const int BOTTOM_MARGIN = SCREEN_HEIGHT - TOP_MARGIN;

const int MIN_SPEED = 3;
const int MAX_SPEED = 6;

const float TURN_FACTOR = 0.3;

const int PROTECTED_RANGE = 30;
const int VISUAL_RANGE = 90;

const float ALIGNMENT_FACTOR = 0.09;
const float COHESION_FACTOR = 0.0005;
const float SEPERATION_FACTOR = 0.05;
