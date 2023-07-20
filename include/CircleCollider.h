#pragma once

#include "Math.h"

class CircleCollider {
public:
    CircleCollider(Vector2<double>* pos, Vector2<double> offset, double radius);

    bool collides(const CircleCollider* other) const;

    Vector2<double>* getPos() const;

    Vector2<double> getOffset() const;

    Vector2<double> getPosOffsetApplied() const;

    double getRadius() const;
private:
    Vector2<double>* pos;
    Vector2<double> offset;
    double radius;
};
