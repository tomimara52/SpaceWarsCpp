#include <cstdint>

#include "Constants.h"
#include "Player.h"
#include "Entity.h"
#include "Math.h"

Player::Player(Vector2<posType> pos, Vector2<posType> dir, SDL_Texture* tex)
	: Entity(pos, tex), dir{ dir }, events{} { }

Player::Player(posType p_x, posType p_y, posType d_x, posType d_y, SDL_Texture *tex)
	: Entity(p_x, p_y, tex), dir{ Vector2<posType>{ d_x, d_y } }, events{} { }

void Player::setEvents(uint_fast8_t newEvents) {
	events = newEvents;
}	

void Player::simulate(double deltaTime) {
	dir = Vector2<posType>{ };
	if (events & DOWN) {
		Vector2<posType> down{ 0.0f, 1.0f };
		dir += down;
	}

	if (events & RIGHT) {
		Vector2<posType> right{ 1.0f, 0.0f };
		dir += right;
	}

	if (events & LEFT) {
		Vector2<posType> left{ -1.0f, 0.0f };
		dir += left;
	}

	if (events & UP) {
		Vector2<posType> up{ 0.0f, -1.0f };
		dir += up;
	}
	dir.normalize();

	pos += dir;
}
