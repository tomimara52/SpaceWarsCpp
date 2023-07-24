#include <SDL2/SDL.h>
#include <cstdint>

#include "Manager.h"
#include "Math.h"
#include "Constants.h"
#include "Player.h"
#include "Powerup.h"

Manager::Manager(RenderWindow window)
	: gameRunning{ true }, window{ window }, entities{ }, players{ }, 
	  collisionables{ }, toDestroy{ }, deltaTime{ }, prevTime{ },
      prevPrevTime{ }, pEvents{ } {
	SDL_Texture* rocketTex1 = window.loadTexture("/home/tomi/Documents/sdl2-game/res/gfx/rocket-nice-red.png");
	SDL_Texture* rocketTex2 = window.loadTexture("/home/tomi/Documents/sdl2-game/res/gfx/rocket-nice-green.png");

    SDL_Texture* powerupTex = window.loadTexture("/home/tomi/Documents/sdl2-game/res/gfx/dead-touch.png");

	Player* player1 = new Player{ 100, 100, 0, rocketTex1};
	Player* player2 = new Player{ 500, 100, 0, rocketTex2};
	Player* player3 = new Player{ 100, 300, 0, rocketTex2};

    Powerup* deadTouch = new Powerup{ 250, 250, powerupTex, 'd' };

    this->addCollisionable(deadTouch);
    this->addEntity(deadTouch);

	this->addPlayer(player1);
	this->addPlayer(player2);
	this->addPlayer(player3);
}

void Manager::handleEvent(SDL_Event& event) {
	if (event.type == SDL_QUIT)
		gameRunning = false;
}

void Manager::handleKeyboard() {
    size_t n_players = players.size();
	const uint8_t* kbdState{ SDL_GetKeyboardState(NULL) };

    if (n_players >= 1 && *(pEvents[0]) & ALIVE) {
        if (kbdState[SDL_SCANCODE_W]) {
            *(pEvents[0]) = *(pEvents[0]) | FORWARD;
        } else {
            *(pEvents[0]) = *(pEvents[0]) & (~FORWARD);
        }
    }

    if (n_players >= 2 && *(pEvents[1]) & ALIVE) {
        if (kbdState[SDL_SCANCODE_T]) {
            *(pEvents[1]) = *(pEvents[1]) | FORWARD;
        } else {
            *(pEvents[1]) = *(pEvents[1]) & (~FORWARD);
        }
    }

    if (n_players >= 3 && *(pEvents[2]) & ALIVE) {
        if (kbdState[SDL_SCANCODE_U]) {
            *(pEvents[2]) = *(pEvents[2]) | FORWARD;
        } else {
            *(pEvents[2]) = *(pEvents[2]) & (~FORWARD);
        }
    }

    if (n_players >= 4 && *(pEvents[3]) & ALIVE) {
        if (kbdState[SDL_SCANCODE_P]) {
            *(pEvents[3]) = *(pEvents[3]) | FORWARD;
        } else {
            *(pEvents[3]) = *(pEvents[3]) & (~FORWARD);
        }
    }
}

double Manager::updateDeltaTime() {
	prevPrevTime = prevTime;
	prevTime = SDL_GetPerformanceCounter();

	double freq = (double)SDL_GetPerformanceFrequency();
	
	deltaTime = (prevTime - prevPrevTime) / freq;

	return deltaTime;
}

double Manager::getDeltaTime() {
	return deltaTime;
}

bool Manager::isGameRunning() {
	return gameRunning;
}

void Manager::addEntity(Entity* e) {
	entities.push_back(e);
}

void Manager::addPlayer(Player* p) {
	players.push_back(p);
    this->addEntity(p);
    this->addCollisionable(p);
    pEvents.push_back(p->getEvents());
}

void Manager::addCollisionable(Entity* e) {
	collisionables.push_back(e);
}

void Manager::update() {
	this->handleKeyboard();

	for (Entity* e : entities) {
		e->simulate(deltaTime);
	}

    for (size_t i{}; i < collisionables.size(); ++i) {
        Entity* e0{ collisionables[i] };
        for (size_t j{ i+1 }; j < collisionables.size(); ++j) {
            Entity* e1{ collisionables[j] };

            char id0{ e0->getId() };
            char id1{ e1->getId() };

            if (!(e0->collides(e1)))
                continue;

            if (id0 == 'p' && id1 == 'p') {
                auto p0{ dynamic_cast<Player*>(e0) };
                auto p1{ dynamic_cast<Player*>(e1) };

                this->playersCollide(p0, p1);
            } else if (id0 == 'p' && id1 == 'd') {
                auto p{ dynamic_cast<Player*>(e0) };

                this->grabDeadTouch(p, e1);
            } else if (id0 == 'd' && id1 == 'p') {
                auto p{ dynamic_cast<Player*>(e1) };

                this->grabDeadTouch(p, e0);
            }
        }
    }
}

void Manager::render() {

	window.clear();

	for (Entity* e : entities) {
		e->render(window.getRenderer());	
	}

	window.display();
}

void Manager::killPlayer(Player* p) {
    p->setEvents(0);

    this->removeEntity(p);
    this->removeCollisionable(p);
}

void Manager::removeEntity(Entity* e) {
    for (size_t i{}; i < entities.size(); ++i) {
        if (entities.at(i) == e) {
            entities.erase(entities.begin() + i);
            break;
        }
    }
}

void Manager::removeCollisionable(Entity* e) {
    for (size_t i{}; i < collisionables.size(); ++i) {
        if (collisionables.at(i) == e) {
            collisionables.erase(collisionables.begin() + i);
            break;
        }
    }
}

void Manager::playersCollide(Player* p0, Player* p1) {
    if (*(p0->getEvents()) & DEAD_TOUCH) {
        killPlayer(p1);
    }

    if (*(p1->getEvents()) & DEAD_TOUCH) {
        killPlayer(p0);
    }

    Vector2<double> m0{ p0->getMomentum() };            
    Vector2<double> m1{ p1->getMomentum() };            
    Vector2<double> pos0{ p0->getPos() };            
    Vector2<double> pos1{ p1->getPos() };            
    double radius{ p0->getCollider()->getRadius() };

    Vector2<double> dist{ pos0 - pos1 };
    Vector2<double> radiusVec{ dist * (1 / dist.norm()) * radius };
    Vector2<double> correction{ dist - radiusVec * 2 };
    correction = correction * 0.5;

    p0->setPos(pos0 - correction);
    p1->setPos(pos1 + correction);

    double vel{ (m0 - m1).norm() };
    dist.normalize();

    p0->setMomentum(m0 + dist * vel);
    p1->setMomentum(m1 - dist * vel);
}

void Manager::grabDeadTouch(Player* p, Entity* powerup) {
    this->removeEntity(powerup);
    this->removeCollisionable(powerup);

    p->addToEvents(DEAD_TOUCH);
    p->setDeadTouchTime();
}
