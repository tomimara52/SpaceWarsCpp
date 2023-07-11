#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <numbers>


#include "Math.h"
#include "RenderWindow.h"
#include "Entity.h"

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
	: window{ NULL }, renderer{ NULL } {

	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);

	if (window == NULL)
		std::cout << "Window failed to initialize with error: "
		          << SDL_GetError() << "\n";

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filepath) {
	SDL_Texture* texture{};
	texture = IMG_LoadTexture(renderer, p_filepath);

	if (texture == NULL)
		std::cout << "LoadTexture failed with error: " << SDL_GetError() << "\n";

	return texture;
}

void RenderWindow::clear() {
	SDL_RenderClear(renderer);
}

void RenderWindow::display() {
	SDL_RenderPresent(renderer);
}

void RenderWindow::cleanUp() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

SDL_Renderer* RenderWindow::getRenderer() {
	return renderer;
}
