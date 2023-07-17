#pragma once

#include "Math.h"

class CircleCollider {
public:
    CircleCollider(Vector2<double>* pos, double radius);

    bool collides(CircleCollider& other);

    Vector2<double>* getPos() const;

    double getRadius() const;
private:
    Vector2<double>* pos;
    double radius;
};
