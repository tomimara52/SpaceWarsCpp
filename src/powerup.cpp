#include <SDL2/SDL.h>

#include "Powerup.h"
#include "CircleCollider.h"

Powerup::Powerup(double x, double y, SDL_Texture *tex)
    : Entity(x, y, tex, 'w'), collider{ CircleCollider{ &pos, Vector2<double>{ 10, 10 }, 10 } } {
    currentFrame.x = 21;
    currentFrame.y = 21;
    currentFrame.h = 22;
    currentFrame.w = 22;
}

Powerup::Powerup(double x, double y, SDL_Texture* tex, char id) 
    : Entity(x, y, tex, id), collider{ CircleCollider{ &pos, Vector2<double>{ 10, 10 }, 10 } } {
    currentFrame.x = 21;
    currentFrame.y = 21;
    currentFrame.h = 22;
    currentFrame.w = 22;
}

const CircleCollider *Powerup::getCollider() const {
    return &collider;
}

bool Powerup::collides(Entity* other) const {
    const CircleCollider* otherCollider = other->getCollider();

    if (otherCollider == NULL) return false;

    return collider.collides(otherCollider);
}

Vector2<double> Powerup::getPosOffsetApplied() const {
    return collider.getPosOffsetApplied();
}
