#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdint>

#include "Math.h"
#include "Entity.h"

class Player : public Entity {
public:
	Player(Vector2<double> pos, double dir, SDL_Texture* tex);
	Player(double p_x, double p_y, double dir, SDL_Texture* tex);
	void simulate(double deltaTime) override;
	void render(SDL_Renderer* renderer) const override;
	void setEvents(uint_fast8_t newEvents);
	double getDir() const;
private:
	double dir;
	double moveDir;
	double vel;
	uint_fast8_t events;
};

const double ACCELERATION = 80.0;
const double MIN_SPEED = 40.0;
const double MAX_SPEED = 200.0;
const double ROT_SPEED = 5.0;
const double FRICTION = 50.0;
