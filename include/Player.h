#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdint>

#include "Math.h"
#include "Entity.h"
#include "CircleCollider.h"

class Player : public Entity {
public:
	Player(double p_x, double p_y, double dir, SDL_Texture* tex);
	void simulate(double deltaTime) override;
	void render(SDL_Renderer* renderer) const override;
	void setEvents(uint_fast8_t newEvents);
	double getDir() const;
    bool collides(Entity* other) const override;
    const CircleCollider* getCollider() const override;
    Vector2<double> getMomentum() const;
    void setMomentum(Vector2<double>);
    uint_fast8_t* getEvents();
    void addToEvents(uint_fast8_t newEvent);
private:
	double dir;
    Vector2<double> momentum;
	uint_fast8_t events;
    CircleCollider collider;
};

