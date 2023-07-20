#include <cmath>

#include "CircleCollider.h"
#include "Math.h"

CircleCollider::CircleCollider(Vector2<double>* pos, Vector2<double> offset, double radius)
    : pos{ pos }, offset{ offset }, radius{ radius } { }

bool CircleCollider::collides(const CircleCollider* other) const {
    Vector2<double> otherPos = other->getPosOffsetApplied();
    Vector2<double> pos = this->getPosOffsetApplied();

    double distance = sqrt((pos.x - otherPos.x) * (pos.x - otherPos.x) + (pos.y - otherPos.y) * (pos.y - otherPos.y));

    return radius + other->getRadius() >= distance;
}

Vector2<double>* CircleCollider::getPos() const {
    return pos;
}

double CircleCollider::getRadius() const {
    return radius;
}

Vector2<double> CircleCollider::getOffset() const {
    return offset;
}

Vector2<double> CircleCollider::getPosOffsetApplied() const {
    return *pos + offset;
}
