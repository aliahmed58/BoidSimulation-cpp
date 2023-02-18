#include <stdio.h>
#include <vector>
#include "../include/renderer.h"
#include "../include/boid.h"
#include "../include/menu.h"

int random_pos(int max, int min) {
	int range = max - min + 1;
	int num = rand() % range + min;
	return num;
}

void spawn_boid(std::vector<Boid*> &boids, SDL_Renderer* renderer) {
	int x, y;
	SDL_GetMouseState(&x, &y);
	boids.insert(boids.begin(), new Boid(x,y, renderer));
	
}

int main(int argc, char* args[]) {


	Renderer* system = new Renderer();
	SDL_Renderer* renderer = system->getRenderer();

	Texture* bg = new Texture("./res/bg.png", renderer);
	Menu* menu = new Menu(renderer);

	double deltaTime = system->getDeltaTime();

	bool quit = false;

	std::vector<Boid*> boids;
	
	for (int i = 0; i < 1; i ++) {
		Boid* boid = new Boid();
		float x = (float) random_pos(SCREEN_WIDTH, 0);
		float y = (float) random_pos(SCREEN_HEIGHT, 0);
		boids.insert(boids.begin(), new Boid(x, y, renderer));
	}

	SDL_Event e;

	while (!quit) {

		system->updateDeltaTime();
		deltaTime = system->getDeltaTime();
	
		while (SDL_PollEvent(&e) != 0) {

			if (e.type == SDL_QUIT) {
				quit = true;
			}

			if (e.type == SDL_MOUSEBUTTONDOWN) {
				menu->handle_updates(e, boids);
				
				if (e.button.y > 50) {
					spawn_boid(boids, renderer);
					menu->get_controls().boid_count ++;
				}
				
			}
		}

		// set renderer color
		SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255);
		// clear renderer to draw on screen
		SDL_RenderClear(renderer);

		SDL_Rect src = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
		SDL_Rect dst = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
		SDL_SetTextureAlphaMod(bg->getTexture(), 10);
		bg->render(&src, &dst);

		menu->render(renderer);

		for (int i = 0; i < boids.size(); i ++) {
			boids.at(i)->render();
			boids.at(i)->update(deltaTime, boids, menu->get_controls());
		}

		// render above entities
		SDL_RenderPresent(renderer);
	}

	/* deallocating memory used by boids */
	for (int i = 0; i < boids.size(); i ++) delete boids.at(i);
	boids.clear();

	delete menu;
	delete bg;
	delete system;
	return 0;

}