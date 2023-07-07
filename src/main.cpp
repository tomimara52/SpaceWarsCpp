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

	std::vector<Entity> entities{ Entity{ 0, 0, faceTex },
								  Entity{ 0, 33, faceTex },
								  Entity{ 0, 66, faceTex },
								};

	entities.push_back(Entity{ 0, 99, faceTex });

	bool gameRunning{ true };

	SDL_Event event;
	
	while (gameRunning) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				gameRunning = false;
		}

		handler.update();

		//player.dir.print();
		//player.getPos().print();

		player.simulate();
		
		window.clear();

		window.render(player);

		for (Entity e : entities) {
			window.render(e);
		}

		//std::cout << utils::hireTimeInSeconds() << '\n';
		
		window.display();
	}
	
	window.cleanUp();
	SDL_Quit();
	
	return 0;
}
