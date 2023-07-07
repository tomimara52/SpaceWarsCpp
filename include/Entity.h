#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Math.h"

class Entity {
public:
	Entity(Vector2<float> pos, SDL_Texture* tex);
	Entity(float x, float y, SDL_Texture* tex);
	Vector2<float>& getPos();
	SDL_Rect getCurrentFrame();
	SDL_Texture* getTex();
protected:
	Vector2<float> pos;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
};
