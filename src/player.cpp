#include "Player.h"
#include "Entity.h"
#include "Math.h"

Player::Player(Vector2<float> pos, Vector2<float> dir, SDL_Texture* tex)
	: Entity(pos, tex), dir{ dir } { }

Player::Player(float p_x, float p_y, float d_x, float d_y, SDL_Texture *tex)
	: Entity(p_x, p_y, tex), dir{ Vector2<float>{ d_x, d_y } } { }    

void Player::simulate() {
	pos += dir;
}
