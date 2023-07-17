#include "CircleCollider.h"
#include "Math.h"

CircleCollider::CircleCollider(Vector2<double>& pos, char id)
    : pos{ pos }, id{ id } { }

bool CircleCollider::collides(CircleCollider& other) {
    return true;
}

Vector2<double>& CircleCollider::getPos() const {
    return pos;
}

char CircleCollider::getId() const {
    return id;
}
