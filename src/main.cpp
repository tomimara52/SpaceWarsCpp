#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "RenderWindow.h"
#include "Entity.h"
#include "Player.h"
#include "InputHandler.h"

int main(int argc, char* args[]) {
	if (SDL_Init(SDL_INIT_VIDEO) > 0) 
		std::cout << "SDL_Init FAILED WITH ERROR: " << SDL_GetError() << "\n";

	if (!IMG_Init(IMG_INIT_PNG))
		std::cout << "IMG_Init FAILED WITH ERROR: " << SDL_GetError() << "\n";

	RenderWindow window("Game v1", 600, 600);


	SDL_Texture* faceTex = window.loadTexture("res/gfx/face.png");

	Player player{ 100, 100, 0, 0, faceTex };

	InputHandler handler{ player };

	std::vector<Entity*> entities{ &player };

	bool gameRunning{ true };

	SDL_Event event;
	
	while (gameRunning) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				gameRunning = false;
		}

		handler.update();

		player.simulate();
		
		window.clear();

		window.render(player);

		for (Entity* e : entities) {
			window.render(*e);
		}
		
		window.display();
	}
	
	window.cleanUp();
	SDL_Quit();
	
	return 0;
}
