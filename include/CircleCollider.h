#pragma once

#include "Math.h"

class CircleCollider {
public:
    CircleCollider(Vector2<double>* pos);

    bool collides(CircleCollider& other);

    Vector2<double>* getPos() const;

    char getId() const;
private:
    Vector2<double>* pos;
};
