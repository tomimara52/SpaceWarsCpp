#define SHOW_MOMENTUM_VECTORS

#include <cstdint>
#include <cmath>
#include <algorithm>
#include <tuple>
#include <functional>

#include "CircleCollider.h"
#include "Constants.h"
#include "Player.h"
#include "Entity.h"
#include "Math.h"
#include "Color.h"
#include "Bullet.h"

Player::Player(double p_x, double p_y, double dir, SDL_Texture *tex, SDL_Texture* backTex, Color color, shootFuncType shootFunc, int* screen_w, int* screen_h)
	: Entity(p_x, p_y, tex, 'p'), dir{ dir }, momentum{}, events{ ALIVE },
      collider{ CircleCollider{ &pos, Vector2<double>{ 32, 32 }, 26 } },
      shootBullet{ shootFunc }, backTex{ backTex }, color{ color },
      screen_w{ screen_w }, screen_h{ screen_h } {
    currentFrame.h = 64;
    currentFrame.w = 64;
}

void Player::setEvents(uint_fast8_t newEvents) {
	events = newEvents;
}	

void Player::simulate(double deltaTime) {
    this->move(deltaTime);

    if (events & DEAD_TOUCH) {
        deadTouchTime -= deltaTime;
        if (deadTouchTime <= 0) {
            deadTouchTime = 0;
            events = events & (~DEAD_TOUCH);
        }
    }

    if (events & SHOOTER) {
        shooterTime -= deltaTime;
        nextBulletTime -= deltaTime;
        if (shooterTime <= 0) {
            shooterTime = 0;
            events = events & (~SHOOTER);
        } else if (nextBulletTime <= 0) {
            Vector2<double> bulletPos{ getPosOffsetApplied() };
            bulletPos += Vector2<double>{ cos(dir), sin(dir) } * collider.getRadius();

            shootBullet(bulletPos.x, bulletPos.y, dir, color);
            nextBulletTime = SHOOTER_CADENCE;
        }
    }
}

void Player::move(double deltaTime) {
	if (events & FORWARD) {
		const Vector2<double> dirVector{ cos(dir), sin(dir) };

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

    if (pos.x + 32 > *screen_w)
        pos.x -= *screen_w;
    else if (pos.x + 32 < 0)
        pos.x += *screen_w;

    if (pos.y + 32 > *screen_h)
        pos.y -= *screen_h;
    else if (pos.y + 32 < 0)
        pos.y += *screen_h;
}

double Player::getDir() const {
	return dir;
}

void Player::render(SDL_Renderer* renderer) const {
	SDL_Rect src{ this->getCurrentFrame() };
	
	Vector2<double> dstVec{ this->getPos() };
	SDL_Rect dst;
	dst.x = dstVec.x;
	dst.y = dstVec.y;
	dst.w = this->getCurrentFrame().w;
	dst.h = this->getCurrentFrame().h;

	double dirRender = (dir * 180 / PI) + 90;
	/*
	  dir = ( p_dir + (pi/2) ) * (180/pi)	this transforms radians to degrees
	  = (p_dir * (180 / pi)) + 90
	*/

    if (events & DEAD_TOUCH) {
        SDL_Rect dstBack;
        dstBack.x = dstVec.x - 5;
        dstBack.y = dstVec.y - 5;
        dstBack.w = this->getCurrentFrame().w + 10;
        dstBack.h = this->getCurrentFrame().h + 10;

        unsigned int r, g, b;
        std::tie(r, g, b) = getHexColor(color);

        SDL_SetTextureColorMod(backTex, r, g, b);
        SDL_RenderCopyEx(renderer, backTex, &src, &dstBack, dirRender, NULL, SDL_FLIP_NONE);
    }

	SDL_RenderCopyEx(renderer, tex, &src, &dst, dirRender, NULL, SDL_FLIP_NONE);

    #ifdef SHOW_MOMENTUM_VECTORS
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    SDL_RenderDrawLine(renderer, pos.x + 32, pos.y + 32, pos.x + 32 + momentum.x, pos.y + 32 + momentum.y);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    #endif
}

bool Player::collides(Entity* other) const {
    const CircleCollider* otherCollider = other->getCollider();

    if (otherCollider == NULL) return false;

    return collider.collides(otherCollider);
}

const CircleCollider* Player::getCollider() const {
    return &collider;
}

Vector2<double> Player::getMomentum() const {
    return momentum;
}

void Player::setMomentum(Vector2<double> newMomentum) {
    momentum = newMomentum;
}

uint_fast8_t* Player::getEvents() {
    return &events;
}

void Player::addToEvents(uint_fast8_t newEvent) {
    events = events | newEvent;
}

void Player::setDeadTouchTime() {
    deadTouchTime = DEAD_TOUCH_TIME;
}

void Player::setShooterTime() {
    shooterTime = SHOOTER_TIME;
    nextBulletTime = SHOOTER_CADENCE;
}

const Color Player::getColor() const {
    return color;
}

Vector2<double> Player::getPosOffsetApplied() const {
    return collider.getPosOffsetApplied();
}
