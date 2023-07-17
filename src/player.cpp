#include <cstdint>
#include <cmath>
#include <algorithm>

#include "CircleCollider.h"
#include "Constants.h"
#include "Player.h"
#include "Entity.h"
#include "Math.h"

Player::Player(double p_x, double p_y, double dir, SDL_Texture *tex)
	: Entity(p_x, p_y, tex, 'p'), dir{ dir }, momentum{}, events{},
      collider{ CircleCollider{ &pos, 16 } } { }

void Player::setEvents(uint_fast8_t newEvents) {
	events = newEvents;
}	

void Player::simulate(double deltaTime) {
	if (events & FORWARD) {
		Vector2<double> dirVector{ cos(dir), sin(dir) };

        momentum += dirVector * ACCELERATION * deltaTime;

        if (momentum.norm() > MAX_SPEED) {
            momentum.normalize();  
            momentum = momentum * MAX_SPEED;
        }

	} else {
        if (!momentum.isZero()) {
            Vector2<double> friction = momentum * (-1);
            friction.normalize();
            friction = friction * FRICTION * deltaTime;
            if (friction.norm() >= momentum.norm()) {
                momentum = Vector2<double>{ };
            } else {
                momentum = momentum + friction;
            }
        }

		dir = dir + ROT_SPEED * deltaTime;
		double max_angle = 2*PI;
		if (dir >= max_angle) {
			dir = std::fmod(dir, max_angle);
		}

	}
    pos += momentum * deltaTime;
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

	double dirRender = (dir * 180 / PI) + 90;
	/*
	  dir = ( p_dir + (pi/2) ) * (180/pi)	this transforms radians to degrees
	  = (p_dir * (180 / pi)) + 90
	*/

	SDL_RenderCopyEx(renderer, this->getTex(), &src, &dst, dirRender, NULL, SDL_FLIP_NONE);
}

bool Player::collides(Entity* other) const {
    const CircleCollider* otherCollider = other->getCollider();

    if (otherCollider == NULL) return false;

    return collider.collides(otherCollider);
}

const CircleCollider* Player::getCollider() const {
    return &collider;
}

void Player::setMomentum(Vector2<double> newMomentum) {
    momentum = newMomentum;
}
