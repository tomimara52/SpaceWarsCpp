#include "CircleCollider.h"
#include "Math.h"

CircleCollider::CircleCollider(Vector2<double>* pos)
    : pos{ pos } { }

bool CircleCollider::collides(CircleCollider& other) {
    return false;
}

Vector2<double>* CircleCollider::getPos() const {
    return pos;
}
