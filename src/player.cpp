#include <cstdint>
#include <cmath>
#include <numbers>

#include "Constants.h"
#include "Player.h"
#include "Entity.h"
#include "Math.h"

Player::Player(Vector2<double> pos, double dir, SDL_Texture* tex)
	: Entity(pos, tex), dir{ dir }, vel{}, events{} { }

Player::Player(double p_x, double p_y, double dir, SDL_Texture *tex)
	: Entity(p_x, p_y, tex), dir{ dir }, events{} { }

void Player::setEvents(uint_fast8_t newEvents) {
	events = newEvents;
}	

void Player::simulate(double deltaTime) {
	if (events & FORWARD) {
		Vector2<double> dirVector{ cos(dir), sin(dir) };

		vel += (ACCELERATION/2) * deltaTime;
		pos += dirVector * vel * deltaTime;
		vel += (ACCELERATION/2) * deltaTime;
		/*
		* I split the vel increase in two to really make the movement framerate
		* independent. For more info: https://youtu.be/yGhfUcPjXuE?t=641
		*/

		if (vel > MAX_SPEED)
			vel = MAX_SPEED;

	} else {
		vel = MIN_SPEED;

		dir = dir + ROT_SPEED * deltaTime;
		double max_angle = 2*std::numbers::pi;
		if (dir >= max_angle) {
			dir -= max_angle;
		}
	}
}

double Player::getDir() const {
	return dir;
}

void Player::render(SDL_Renderer* renderer) const {
	SDL_Rect src{ this->getCurrentFrame() };
	
	Vector2<double> dstVec{ this->getPos() };
	SDL_Rect dst;
	dst.x = dstVec.x * 2;
	dst.y = dstVec.y * 2;
	dst.w = this->getCurrentFrame().w * 2;
	dst.h = this->getCurrentFrame().h * 2;

	double dirRender = (dir * 180 / std::numbers::pi) + 90;
	/*
	  dir = ( p_dir + (pi/2) ) * (180/pi)	this transforms radians to degrees
	  = (p_dir * (180 / pi)) + 90
	*/

	SDL_RenderCopyEx(renderer, this->getTex(), &src, &dst, dirRender, NULL, SDL_FLIP_NONE);
}
