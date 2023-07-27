#pragma once

#include <SDL2/SDL.h>

#include "CircleCollider.h"
#include "Math.h"
#include "Entity.h"

class Powerup : public Entity {
public:
    Powerup(double x, double y, SDL_Texture* tex);
    Powerup(double x, double y, SDL_Texture* tex, char id);
    const CircleCollider* getCollider() const override; 
    bool collides(Entity* other) const override;
    Vector2<double> getPosOffsetApplied() const override;
private:
    CircleCollider collider;
};
