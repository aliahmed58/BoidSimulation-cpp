#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include "constants.h"

class Renderer {
public:
	Renderer();
	~Renderer();

	SDL_Renderer* getRenderer();
	void close();
	
	// calculate delta time
	void updateDeltaTime();
	double getDeltaTime();



private:
	// initialzing SDL
	bool initSDL();

	// private instance of renderer
	SDL_Renderer* renderer;
	SDL_Window* window;

	// delta time variables
	Uint64 NOW;
	Uint64 LAST;
	double deltaTime;
	

};