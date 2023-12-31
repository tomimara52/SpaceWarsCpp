#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "RenderWindow.h"
#include "Entity.h"
#include "Player.h"
#include "Manager.h"
#include "Powerup.h"

int main(int argc, char* args[]) {

	if (SDL_Init(SDL_INIT_EVERYTHING) > 0) 
		std::cout << "SDL_Init FAILED WITH ERROR: " << SDL_GetError() << "\n";

	if (!IMG_Init(IMG_INIT_PNG))
		std::cout << "IMG_Init FAILED WITH ERROR: " << SDL_GetError() << "\n";

	RenderWindow window{ "Game v1" };


	Manager* manager = new Manager{ window, 4 };


	SDL_Event event;

	while (manager->isGameRunning()) {

		while (SDL_PollEvent(&event)) {
			manager->handleEvent(event);
		}

		manager->update();

		manager->render();
	}

    delete manager;
	

    IMG_Quit();
    SDL_Quit();
    
	
	return 0;
}
