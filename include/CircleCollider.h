#pragma once

#include "Math.h"

class CircleCollider {
public:
    CircleCollider(Vector2<double>* pos, double radius);

    bool collides(const CircleCollider* other) const;

    Vector2<double>* getPos() const;

    double getRadius() const;
private:
    Vector2<double>* pos;
    double radius;
};
