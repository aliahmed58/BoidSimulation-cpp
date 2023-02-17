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
				menu->handle_updates(e);
				spawn_boid(boids, renderer);
				
			}
		}

		// set renderer color
		SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255);
		// clear renderer to draw on screen
		SDL_RenderClear(renderer);

		menu->render(renderer);

		for (int i = 0; i < boids.size(); i ++) {
			boids.at(i)->render();
			boids.at(i)->update(deltaTime, boids, menu->get_controls());
		}

		// render above entities
		SDL_RenderPresent(renderer);
	}

	delete menu;
	delete system;
	return 0;

}