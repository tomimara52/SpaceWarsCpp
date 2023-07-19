#include "Powerup.h"
#include "CircleCollider.h"

Powerup::Powerup(double x, double y, SDL_Texture *tex)
    : Entity(x, y, tex, 'w'), collider{ CircleCollider{ &pos, 10 } } {
    currentFrame.h = 20;
    currentFrame.w = 20;
}

const CircleCollider *Powerup::getCollider() const {
    return &collider;
}

bool Powerup::collides(Entity* other) const {
    const CircleCollider* otherCollider = other->getCollider();

    if (otherCollider == NULL) return false;

    return collider.collides(otherCollider);
}