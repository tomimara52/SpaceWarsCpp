#pragma once
#include <SDL2/SDL.h>

#include "Math.h"


class Entity {
public:
	Entity(Vector2<double> pos, SDL_Texture* tex);
	Entity(double x, double y, SDL_Texture* tex);
	Vector2<double> getPos() const;
	SDL_Rect getCurrentFrame() const;
	SDL_Texture* getTex() const;
	virtual void simulate(double deltaTime);
	virtual void render(SDL_Renderer* renderer) const;
    virtual bool collides(Entity* other) const;
    char getId() const;
protected:
	Vector2<double> pos;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
    char id;
};
