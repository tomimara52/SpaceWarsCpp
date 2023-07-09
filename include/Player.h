#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdint>

#include "Math.h"
#include "Entity.h"
#include "Constants.h"

class Player : public Entity {
public:
	Player(Vector2<posType> pos, Vector2<posType> dir, SDL_Texture* tex);
	Player(posType p_x, posType p_y, posType d_x, posType d_y, SDL_Texture* tex);
	void simulate(posType deltaTime) override;
	Vector2<posType> dir;
	void setEvents(uint_fast8_t newEvents);
private:
	uint_fast8_t events;
};
