#pragma once
#include <SDL_ttf.h>
#include <SDL.h>
#include <SDL_image.h>
#include "constants.h"
#include <string>

/* Class to store and initialize the font */
class Font {
public:
	Font();

	/* params: font file path, renderer, and font size */
	Font(std::string filename, SDL_Renderer* gRenderer, int size);
	~Font();

	/* renders a string given x, y coordinates and a color */
	void render(int x, int y, std::string text, SDL_Color color);

	/* returns the width and height of the font rendered */
	int getWidth();
	int getHeight();


private:
	std::string filename;
	SDL_Renderer* renderer;
	TTF_Font* font;
	int height;
	int width;

	/* loads the font */
	bool loadFont(int size);

};