#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "Constants.h"
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

	RenderWindow window{ "Game v1", SCREEN_W, SCREEN_H };


	SDL_Texture* rocketTex1 = window.loadTexture("res/gfx/rocket-nice-red.png");
	SDL_Texture* rocketTex2 = window.loadTexture("res/gfx/rocket-nice-green.png");

    SDL_Texture* powerupTex = window.loadTexture("res/gfx/dead-touch.png");

	Player player1{ 100, 100, 0, rocketTex1};
	Player player2{ 500, 100, 0, rocketTex2};
	Player player3{ 100, 300, 0, rocketTex2};

    Powerup deadTouch{ 250, 250, powerupTex, 'd' };

	Manager manager{ window };
    manager.addCollisionable(&deadTouch);
    manager.addEntity(&deadTouch);

	manager.addPlayer(&player1);
	manager.addPlayer(&player2);
	manager.addPlayer(&player3);


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

    IMG_Quit();
    SDL_Quit();
    
	
	return 0;
}
