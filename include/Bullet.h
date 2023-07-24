#pragma once

#include <SDL2/SDL.h>

#include "CircleCollider.h"
#include "Entity.h"

class Bullet : public Entity {
public:
    Bullet(double x, double y, double dir, double speed, SDL_Texture* tex);

    const CircleCollider* getCollider() const override; 

    bool collides(Entity* other) const override;

	void simulate(double deltaTime) override;
private:
    CircleCollider collider;
    const double dir;
    const double speed;
};
