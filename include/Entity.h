#pragma once
#include <SDL2/SDL.h>

#include "Math.h"


class Entity {
public:
	Entity(Vector2<double> pos, SDL_Texture* tex);
	Entity(double x, double y, SDL_Texture* tex);
	Vector2<double>& getPos();
	SDL_Rect getCurrentFrame();
	SDL_Texture* getTex();
	virtual void simulate(double deltaTime);
protected:
	Vector2<double> pos;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
};
