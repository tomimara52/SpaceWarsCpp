#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath>
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


	SDL_Texture* faceTex = window.loadTexture("res/gfx/face.png");

	Player player{ 100, 100, 0, 0, faceTex };

	Manager manager{ };

	std::vector<Entity*> entities{ &player };

	SDL_Event event;

	double deltaTime{};

	while (manager.isGameRunning()) {
		
		deltaTime = manager.updateDeltaTime();

		while (SDL_PollEvent(&event)) {
			manager.handleEvent(event);
		}

		manager.handleKeyboard();

		player.setEvents(manager.getP1Events());

		player.simulate(deltaTime);
		
		window.clear();

		for (Entity* e : entities) {
			window.render(*e);
		}
		
		window.display();

		manager.resetEvents();
	}
	
	window.cleanUp();
	SDL_Quit();
	
	return 0;
}
