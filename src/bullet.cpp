#include <SDL2/SDL.h>

#include <cmath>

#include "Bullet.h"
#include "CircleCollider.h"
#include "Color.h"

Bullet::Bullet(double x, double y, double dir, double speed, SDL_Texture *tex, Color color)
    : Entity(x, y, tex, 'b'),
      collider{ CircleCollider{ &pos, Vector2<double>{ 5, 5 }, 5 } },
      dir{ dir }, speed{ speed }, color{ color } {
    currentFrame.x = 6;
    currentFrame.y = 6;
    currentFrame.h = 10;
    currentFrame.w = 10;
}

const CircleCollider* Bullet::getCollider() const {
    return &collider;
}

bool Bullet::collides(Entity* other) const {
    const CircleCollider* otherCollider = other->getCollider();

    if (otherCollider == NULL) return false;

    return collider.collides(otherCollider);
}

void Bullet::simulate(double deltaTime) {
    pos.x += cos(dir) * speed * deltaTime;
    pos.y += sin(dir) * speed * deltaTime;
}

const Color Bullet::getColor() const {
    return color;
}
