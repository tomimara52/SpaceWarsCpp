#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdint>

#include "Math.h"
#include "Entity.h"

class Player : public Entity {
public:
	Player(Vector2<double> pos, Vector2<double> dir, SDL_Texture* tex);
	Player(double p_x, double p_y, double d_x, double d_y, SDL_Texture* tex);
	void simulate(double deltaTime) override;
	void setEvents(uint_fast8_t newEvents);

private:
	Vector2<double> dir;
	double vel;
	uint_fast8_t events;
};
