#include <SDL2/SDL.h>

#include "Entity.h"
#include "Math.h"


Entity::Entity(Vector2<double> pos, SDL_Texture* tex)
	: pos{ pos }, tex{ tex } {
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 32;
	currentFrame.h = 32;
}

Entity::Entity(double x, double y, SDL_Texture* tex)
	: pos{ Vector2<double>{ x, y } }, tex{ tex } {
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 32;
	currentFrame.h = 32;
}

Vector2<double>& Entity::getPos() {
	return pos;
}


SDL_Rect Entity::getCurrentFrame() {
	return currentFrame;
}
SDL_Texture* Entity::getTex() {
	return tex;
}

void Entity::simulate(double dTime) {
}
