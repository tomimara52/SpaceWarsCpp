#include "CircleCollider.h"
#include "Math.h"

CircleCollider::CircleCollider(Vector2<double>* pos, double radius)
    : pos{ pos }, radius{ radius } { }

bool CircleCollider::collides(CircleCollider& other) {
    return false;
}

Vector2<double>* CircleCollider::getPos() const {
    return pos;
}

double CircleCollider::getRadius() const {
    return radius;
}
