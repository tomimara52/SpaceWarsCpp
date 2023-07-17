#include <cmath>

#include "CircleCollider.h"
#include "Math.h"

CircleCollider::CircleCollider(Vector2<double>* pos, double radius)
    : pos{ pos }, radius{ radius } { }

bool CircleCollider::collides(const CircleCollider* other) const {
    Vector2<double>* otherPos = other->getPos();

    double distance = sqrt((pos->x - otherPos->x) * (pos->x - otherPos->x) + (pos->y - otherPos->y) * (pos->y - otherPos->y));

    return radius + other->getRadius() >= distance;
}

Vector2<double>* CircleCollider::getPos() const {
    return pos;
}

double CircleCollider::getRadius() const {
    return radius;
}
