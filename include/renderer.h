#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
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
