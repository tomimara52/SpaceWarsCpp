#pragma once

#include "Math.h"

class CircleCollider {
    CircleCollider(Vector2<double>& pos, char id);

    bool collides(CircleCollider& other);

    Vector2<double>& getPos() const;

    char getId() const;
private:
    Vector2<double>& pos;
    char id;
};
