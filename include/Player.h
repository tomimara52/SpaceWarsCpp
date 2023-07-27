#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdint>
#include <functional>

#include "Color.h"
#include "Math.h"
#include "Entity.h"
#include "CircleCollider.h"
#include "Bullet.h"

typedef std::function<void(double, double, double, Color)> shootFuncType;

class Player : public Entity {
public:
	Player(double p_x, double p_y, double dir, SDL_Texture* tex, SDL_Texture* backTex, Color color, shootFuncType shootFunc);

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

    void setDeadTouchTime();

    void setShooterTime();

    const Color getColor() const;

    Vector2<double> getPosOffsetApplied() const override;
private:
	void move(double deltaTime);

	double dir;
    Vector2<double> momentum;
	uint_fast8_t events;
    CircleCollider collider;

    double deadTouchTime; 

    double shooterTime;
    double nextBulletTime;

    shootFuncType shootBullet;

    SDL_Texture* backTex;

    const Color color;
};

