#include <cstdint>

#include "Constants.h"
#include "Player.h"
#include "Entity.h"
#include "Math.h"

Player::Player(Vector2<float> pos, Vector2<float> dir, SDL_Texture* tex)
	: Entity(pos, tex), dir{ dir }, events{} { }

Player::Player(float p_x, float p_y, float d_x, float d_y, SDL_Texture *tex)
	: Entity(p_x, p_y, tex), dir{ Vector2<float>{ d_x, d_y } }, events{} { }

void Player::setEvents(uint_fast8_t newEvents) {
	events = newEvents;
}	

void Player::simulate() {
	dir = Vector2<float>{ 0, 0 };
	if (events & DOWN) {
		Vector2<float> down{ 0.0f, 1.0f };
		dir += down;
	}

	if (events & RIGHT) {
		Vector2<float> right{ 1.0f, 0.0f };
		dir += right;
	}

	if (events & LEFT) {
		Vector2<float> left{ -1.0f, 0.0f };
		dir += left;
	}

	if (events & UP) {
		Vector2<float> up{ 0.0f, -1.0f };
		dir += up;
	}
	dir.normalize();

	pos += dir;
}
