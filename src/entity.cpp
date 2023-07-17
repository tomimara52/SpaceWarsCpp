#include <SDL2/SDL.h>

#include "Entity.h"
#include "Math.h"

Entity::Entity(double x, double y, SDL_Texture* tex)
	: pos{ Vector2<double>{ x, y } }, tex{ tex }, id{ } {
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 32;
	currentFrame.h = 32;
}

Vector2<double> Entity::getPos() const {
	return pos;
}


SDL_Rect Entity::getCurrentFrame() const {
	return currentFrame;
}
SDL_Texture* Entity::getTex() const {
	return tex;
}

void Entity::simulate(double dTime) {
}

void Entity::render(SDL_Renderer* renderer) const {
	SDL_Rect src{ currentFrame };
	
	SDL_Rect dst;
	dst.x = pos.x * 2;
	dst.y = pos.y * 2;
	dst.w = currentFrame.w * 2;
	dst.h = currentFrame.h * 2;

	SDL_RenderCopy(renderer, tex, &src, &dst);
}

bool Entity::collides(Entity* other) const {
    return false;
}

char Entity::getId() const {
    return id;
}
