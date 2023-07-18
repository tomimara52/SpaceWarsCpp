#pragma once

#include "CircleCollider.h"
#include "Math.h"
#include "Entity.h"

class Powerup : public Entity {
public:
    Powerup(double x, double y, SDL_Texture* tex);
    const CircleCollider* getCollider() const override; 
    bool collides(Entity* other) const override;
private:
    CircleCollider collider;
};
