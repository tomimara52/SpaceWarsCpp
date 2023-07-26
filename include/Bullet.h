#pragma once

#include <SDL2/SDL.h>

#include "CircleCollider.h"
#include "Entity.h"
#include "Color.h"

class Bullet : public Entity {
public:
    Bullet(double x, double y, double dir, double speed, SDL_Texture* tex, Color color);

    const CircleCollider* getCollider() const override; 

    bool collides(Entity* other) const override;

	void simulate(double deltaTime) override;

    const Color getColor() const;

    void render(SDL_Renderer* renderer) const override;

    Vector2<double> getPosOffsetApplied() const override;
private:
    CircleCollider collider;
    const double dir;
    const double speed;
    const Color color;
};
