#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "RenderWindow.h"

int main(int argc, char* args[]) {
	if (SDL_Init(SDL_INIT_VIDEO) > 0) 
		std::cout << "SDL_Init FAILED WITH ERROR: " << SDL_GetError() << "\n";

	if (!IMG_Init(IMG_INIT_PNG))
		std::cout << "IMG_Init FAILED WITH ERROR: " << SDL_GetError() << "\n";

	RenderWindow window("Game v1", 500, 500);

	SDL_Texture* star = window.loadTexture("res/gfx/star.png");

	bool gameRunning{ true };

	SDL_Event event;
	
	while (gameRunning) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				gameRunning = false;
		}
	}
	
	window.cleanUp();
	SDL_Quit();
	
	return 0;
}
