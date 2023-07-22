#pragma once

#include <SDL2/SDL.h> 
#include <cstdint>
#include <vector>

#include "Entity.h"
#include "Player.h"
#include "RenderWindow.h"

class Manager {
public:
	Manager(RenderWindow window);

	void handleEvent(SDL_Event&);

	void handleKeyboard();

	double updateDeltaTime();

	double getDeltaTime();

	bool isGameRunning();

	void addEntity(Entity* e);

	void addPlayer(Player* p);

	void addCollisionable(Entity* e);

	void update();

	void render();

private:
    void killPlayer(Player* p);

    void removeEntity(Entity* e);

    void removeCollisionable(Entity* e);

    void playersCollide(Player* p0, Player* p1);

	bool gameRunning;
	RenderWindow window;
	std::vector<Entity*> entities;
	std::vector<Player*> players;
	std::vector<Entity*> collisionables;
	double deltaTime;
	uint64_t prevTime;
	uint64_t prevPrevTime;
    std::vector<uint_fast8_t*> pEvents;
};
