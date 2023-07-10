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
		Vector2<double> down{ 0.0f, 1.0f };
		dir += down;
	}

	if (events & RIGHT) {
		Vector2<double> right{ 1.0f, 0.0f };
		dir += right;
	}

	if (events & LEFT) {
		Vector2<double> left{ -1.0f, 0.0f };
		dir += left;
	}

	if (events & UP) {
		Vector2<double> up{ 0.0f, -1.0f };
		dir += up;
	}
	dir.normalize();

	pos = pos + dir;
}
