#include <SDL2/SDL.h>
#include <cstdint>

#include "Manager.h"
#include "Math.h"
#include "Constants.h"
#include "Player.h"
#include "Powerup.h"
#include "Bullet.h"
#include "Color.h"

static const int P_RED_TEX = 0;
static const int P_GREEN_TEX = 1;
static const int P_BLUE_TEX = 5;
static const int P_YELLOW_TEX = 6;
static const int DEAD_TOUCH_TEX = 2;
static const int BULLET_TEX = 3;
static const int P_BACK_TEX = 4;
static const int B_EXPLOSION_TEX = 7;

Manager::Manager(RenderWindow window)
	: gameRunning{ true }, window{ window }, entities{ }, players{ }, 
	  collisionables{ }, toDestroy{ }, deltaTime{ }, prevTime{ },
      prevPrevTime{ }, pEvents{ } {
	textures[P_RED_TEX] = window.loadTexture("res/gfx/rocket-nice-red.png");
	textures[P_GREEN_TEX] = window.loadTexture("res/gfx/rocket-nice-green.png");
	textures[P_BLUE_TEX] = window.loadTexture("res/gfx/rocket-nice-blue.png");
	textures[P_YELLOW_TEX] = window.loadTexture("res/gfx/rocket-nice-yellow.png");
    textures[DEAD_TOUCH_TEX] = window.loadTexture("res/gfx/dead-touch.png");
    textures[BULLET_TEX] = window.loadTexture("res/gfx/bullet.png");
    textures[P_BACK_TEX] = window.loadTexture("res/gfx/rocket-nice-back.png");
    textures[B_EXPLOSION_TEX] = window.loadTexture("res/gfx/bullet-explosion.png");

	Player* player1 = new Player{ 100, 100, 0, textures[P_RED_TEX], textures[P_BACK_TEX], Color::red };
	Player* player2 = new Player{ 500, 100, 0, textures[P_GREEN_TEX], textures[P_BACK_TEX], Color::green };
	Player* player3 = new Player{ 100, 300, 0, textures[P_BLUE_TEX], textures[P_BACK_TEX], Color::blue };
	Player* player4 = new Player{ 500, 300, 0, textures[P_YELLOW_TEX], textures[P_BACK_TEX], Color::yellow };

    Powerup* bExplosion = new Powerup{ 400 , 250, textures[B_EXPLOSION_TEX], 'x' };
    Powerup* deadTouch = new Powerup{ 250, 250, textures[DEAD_TOUCH_TEX], 'd' };

    /*
    for (size_t i{}; i < 8; ++i) {
        Bullet* bullet = new Bullet{ 250, 250, (PI*i)/4, BULLET_SPEED_0 , textures[BULLET_TEX]};
        this->addCollisionable(bullet);
        this->addEntity(bullet);
    }
    */
    this->addCollisionable(bExplosion);
    this->addEntity(bExplosion);

    this->addCollisionable(deadTouch);
    this->addEntity(deadTouch);

	this->addPlayer(player1);
	this->addPlayer(player2);
	this->addPlayer(player3);
	this->addPlayer(player4);

}

void Manager::handleEvent(SDL_Event& event) {
	if (event.type == SDL_QUIT)
		gameRunning = false;
}

void Manager::handleKeyboard() {
    const size_t n_players = players.size();
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

	const double freq = (double)SDL_GetPerformanceFrequency();
	
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

        const Vector2<double> ePos{ e0->getPosOffsetApplied() };

        if (ePos.x < 0 || ePos.x > SCREEN_W || ePos.y < 0 || ePos.y > SCREEN_H) {
            toDestroy.push_back(e0);
            continue;
        }

        for (size_t j{ i+1 }; j < collisionables.size(); ++j) {
            Entity* e1{ collisionables[j] };

            const char id0{ e0->getId() };
            const char id1{ e1->getId() };

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
            } else if (id0 == 'p' && id1 == 'b') {
                auto p{ dynamic_cast<Player*>(e0) };

                hitBullet(p, e1);
            } else if (id0 == 'b' && id1 == 'p') {
                auto p{ dynamic_cast<Player*>(e1) };

                hitBullet(p, e0);
            } else if (id0 == 'p' && id1 == 'x') {
                auto p{ dynamic_cast<Player*>(e0) };

                this->spawnBulletExplosion(p, e1);
            } else if (id0 == 'x' && id1 == 'p') {
                auto p{ dynamic_cast<Player*>(e1) };

                this->spawnBulletExplosion(p, e0);
            }
        }
    }

    const size_t toDestroy_size = toDestroy.size();

    for (size_t i{}; i < toDestroy_size; ++i) {
        Entity* elem{ toDestroy.at(i) };
        this->removeCollisionable(elem);
        this->removeEntity(elem);

        delete elem;
    }

    toDestroy.clear();

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

    const Vector2<double> m0{ p0->getMomentum() };            
    const Vector2<double> m1{ p1->getMomentum() };            
    const Vector2<double> pos0{ p0->getPos() };            
    const Vector2<double> pos1{ p1->getPos() };            
    const double radius{ p0->getCollider()->getRadius() };

    Vector2<double> dist{ pos0 - pos1 };
    const Vector2<double> radiusVec{ dist * (1 / dist.norm()) * radius };
    Vector2<double> correction{ dist - radiusVec * 2 };
    correction = correction * 0.5;

    p0->setPos(pos0 - correction);
    p1->setPos(pos1 + correction);

    const double vel{ (m0 - m1).norm() };
    dist.normalize();

    p0->setMomentum(m0 + dist * vel);
    p1->setMomentum(m1 - dist * vel);
}

void Manager::grabDeadTouch(Player* p, Entity* powerup) {
    (this->toDestroy).push_back(powerup);

    p->addToEvents(DEAD_TOUCH);
    p->setDeadTouchTime();
}

Manager::~Manager() {
    const size_t players_size = players.size();

    for (size_t i{}; i < players_size; ++i) {
        Player* player{ players.at(i) };

        this->removeEntity(player);
        this->removeCollisionable(player);

        delete player;
    }

    const size_t entities_size = entities.size();

    for (size_t i{}; i < entities_size; ++i) {
        delete entities.at(i);
    }

    window.cleanUp();
}

void Manager::hitBullet(Player* p, Entity* bullet) {
    const auto bulletBullet = dynamic_cast<Bullet*>(bullet);
    if (p->getColor() != bulletBullet->getColor()) {
        (this->toDestroy).push_back(bullet);

        killPlayer(p);
    }
}

void Manager::spawnBulletExplosion(Player* p, Entity* powerup) {
    toDestroy.push_back(powerup);

    const Vector2<double> pos{ powerup->getCollider()->getPosOffsetApplied() };
    for (size_t i{}; i < 8; ++i) {
        Bullet* bullet = new Bullet{ pos.x , pos.y, (PI*i)/4, BULLET_SPEED_0 , textures[BULLET_TEX], p->getColor() };
        this->addCollisionable(bullet);
        this->addEntity(bullet);
    }
}
