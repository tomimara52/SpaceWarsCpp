#pragma once
#include <SDL2/SDL.h>

#include "Math.h"
#include "CircleCollider.h"

class Entity {
public:
	Entity(double x, double y, SDL_Texture* tex);
	Entity(double x, double y, SDL_Texture* tex, char id);
	Vector2<double> getPos() const;
	SDL_Rect getCurrentFrame() const;
	SDL_Texture* getTex() const;
	virtual void simulate(double deltaTime);
	virtual void render(SDL_Renderer* renderer) const;
    virtual bool collides(Entity* other) const;
    char getId() const;
    virtual CircleCollider* getCollider() const;
protected:
	Vector2<double> pos;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
    char id;
};
