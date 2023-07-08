#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Math.h"
#include "Constants.h"


class Entity {
public:
	Entity(Vector2<posType> pos, SDL_Texture* tex);
	Entity(posType x, posType y, SDL_Texture* tex);
	Vector2<posType>& getPos();
	SDL_Rect getCurrentFrame();
	SDL_Texture* getTex();
protected:
	Vector2<posType> pos;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
};
