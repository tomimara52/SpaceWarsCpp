#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "RenderWindow.h"
#include "Entity.h"
#include "Player.h"
#include "Manager.h"

int main(int argc, char* args[]) {
	if (SDL_Init(SDL_INIT_VIDEO) > 0) 
		std::cout << "SDL_Init FAILED WITH ERROR: " << SDL_GetError() << "\n";

	if (!IMG_Init(IMG_INIT_PNG))
		std::cout << "IMG_Init FAILED WITH ERROR: " << SDL_GetError() << "\n";

	RenderWindow window("Game v1", 600, 600);


	SDL_Texture* faceTex = window.loadTexture("res/gfx/rocket1.png");

	Player player{ 100, 100, 0, faceTex };

	Manager manager{ window };
	manager.addPlayer(&player);
	manager.addCollisionable(&player);

	SDL_Event event;

	while (manager.isGameRunning()) {

		manager.updateDeltaTime();

		while (SDL_PollEvent(&event)) {
			manager.handleEvent(event);
		}

		manager.update();

		manager.render();
	}
	
	window.cleanUp();
	SDL_Quit();
	
	return 0;
}
