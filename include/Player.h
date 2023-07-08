#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdint>

#include "Math.h"
#include "Entity.h"

class Player : public Entity {
public:
	Player(Vector2<float> pos, Vector2<float> dir, SDL_Texture* tex);
	Player(float p_x, float p_y, float d_x, float d_y, SDL_Texture* tex);
	void simulate();
	Vector2<float> dir;
	void setEvents(uint_fast8_t newEvents);
private:
	uint_fast8_t events;
};
