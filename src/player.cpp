#include <cstdint>

#include "Constants.h"
#include "Player.h"
#include "Entity.h"
#include "Math.h"

Player::Player(Vector2<double> pos, Vector2<double> dir, SDL_Texture* tex)
	: Entity(pos, tex), dir{ dir }, vel{}, events{} { }

Player::Player(double p_x, double p_y, double d_x, double d_y, SDL_Texture *tex)
	: Entity(p_x, p_y, tex), dir{ Vector2<double>{ d_x, d_y } }, events{} { }

void Player::setEvents(uint_fast8_t newEvents) {
	events = newEvents;
}	

void Player::simulate(double deltaTime) {
	dir = Vector2<double>{ };
	if (events & DOWN) {
		dir += Vector2<double>{ 0.0, 1.0 };
	}

	if (events & RIGHT) {
		dir += Vector2<double>{ 1.0, 0.0 };
	}

	if (events & LEFT) {
		dir += Vector2<double>{ -1.0, 0.0 };
	}

	if (events & UP) {
		dir += Vector2<double>{ 0.0, -1.0 };
	}
	dir.normalize();

	pos += dir * 50 * deltaTime;
}
