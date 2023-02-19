#include <stdio.h>
#include <vector>
#include "../include/renderer.h"
#include "../include/boid.h"
#include "../include/menu.h"

/* returns a random position between given max and min range */
int random_pos(int max, int min) {
	int range = max - min + 1;
	int num = rand() % range + min;
	return num;
}

/* spawns boid on the screen and adds them to the vector */
void spawn_boid(std::vector<Boid*> &boids, SDL_Renderer* renderer) {
	int x, y;
	SDL_GetMouseState(&x, &y);
	boids.insert(boids.begin(), new Boid(x,y, renderer));
	
}

int main(int argc, char* args[]) {

	/* Creates a Renderer* pointer */
	Renderer* system = new Renderer();

	/* get renderer after initializing it */
	SDL_Renderer* renderer = system->getRenderer();

	/* create a background texture */
	Texture* bg = new Texture("./res/bg.png", renderer);

	/* create a menu object */
	Menu* menu = new Menu(renderer);

	/* get deltatime from system */
	double deltaTime = system->getDeltaTime();

	/* simulation loop variable */
	bool quit = false;

	/* initialize a vector to store boid pointers */
	std::vector<Boid*> boids;
	
	/* add boids before the start of main loop based on the INITIAL_BOID count in constants.h file */
	for (int i = 0; i < INITIAL_BOIDS; i ++) {
		Boid* boid = new Boid();
		float x = (float) random_pos(SCREEN_WIDTH, 0);
		float y = (float) random_pos(SCREEN_HEIGHT, 0);
		boids.insert(boids.begin(), new Boid(x, y, renderer));
	}

	/* SDL_Event e for taking keyboard and mouse events */
	SDL_Event e;

	/* keep running until quit is set to true */
	while (!quit) {

		/* update deltatime */
		system->updateDeltaTime();

		/* and get the updated deltatime */
		deltaTime = system->getDeltaTime();
	
		/* if events exist */
		while (SDL_PollEvent(&e) != 0) {

			/* if the program is exited, set quit to true and break main loop */
			if (e.type == SDL_QUIT) {
				quit = true;
			}

			/* if mouse button is clicked, handle updates on UI */
			if (e.type == SDL_MOUSEBUTTONDOWN) {
				menu->handle_updates(e, boids);
				
				/* if the button click is below the menu controls, spawn a new boid */
				if (e.button.y > 50) {
					spawn_boid(boids, renderer);

					/* increment the no. of boids */
					menu->get_controls().boid_count ++;
				}
				
			}
		}

		// set renderer color
		SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255);
		// clear renderer to draw on screen
		SDL_RenderClear(renderer);

		/* render the background texture on screen  */
		SDL_Rect src = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
		SDL_Rect dst = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
		SDL_SetTextureAlphaMod(bg->getTexture(), 10);
		bg->render(&src, &dst);

		/* render menu */
		menu->render(renderer);

		/* render all boids and call update method on them */
		for (int i = 0; i < boids.size(); i ++) {
			boids.at(i)->render();
			boids.at(i)->update(deltaTime, boids, menu->get_controls());
		}

		// render above entities
		SDL_RenderPresent(renderer);
	}

	/* deallocating memory used by boids */
	for (int i = 0; i < boids.size(); i ++) delete boids.at(i);

	/* clear the boids vector */
	boids.clear();

	/* deallocate all pointers created with new */
	delete menu;
	delete bg;
	delete system;
	return 0;

}