#include <SDL2/SDL.h>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <functional>

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
static const int SHOOTER_TEX = 8;

Manager::Manager(RenderWindow window, size_t nPlayers)
	: gameRunning{ true }, window{ window }, entities{ }, players{ }, 
	  playersAlive{}, collisionables{ }, toDestroy{ }, deltaTime{ }, prevTime{ },
      prevPrevTime{ }, pEvents{ } {
	textures[P_RED_TEX] = window.loadTexture("res/gfx/rocket-nice-red.png");
	textures[P_GREEN_TEX] = window.loadTexture("res/gfx/rocket-nice-green.png");
	textures[P_BLUE_TEX] = window.loadTexture("res/gfx/rocket-nice-blue.png");
	textures[P_YELLOW_TEX] = window.loadTexture("res/gfx/rocket-nice-yellow.png");
    textures[DEAD_TOUCH_TEX] = window.loadTexture("res/gfx/dead-touch.png");
    textures[BULLET_TEX] = window.loadTexture("res/gfx/bullet.png");
    textures[P_BACK_TEX] = window.loadTexture("res/gfx/rocket-nice-back.png");
    textures[B_EXPLOSION_TEX] = window.loadTexture("res/gfx/bullet-explosion.png");
    textures[SHOOTER_TEX] = window.loadTexture("res/gfx/shooter.png");

    SDL_GetWindowSize(window.getWindow(), &screen_w, &screen_h);

    std::srand(std::time(NULL));

    newTimeToNextSpawn();

    shootFuncType shootBullet{ [this](double x, double y, double dir, Color color) -> void {
        Bullet* const newBullet = new Bullet(x, y, dir, SHOOTER_BULLET_SPEED, textures[BULLET_TEX], color);
        this->entities.push_back(newBullet);
        this->collisionables.push_back(newBullet);
    } };

    const Color colors[]{ Color::red, Color::blue, Color::yellow, Color::green };
    const std::tuple<double, double> positions[]{ {100, 100}, {500, 100}, {100, 300}, {500, 300} };
    SDL_Texture* const pTextures[]{ textures[P_RED_TEX], textures[P_BLUE_TEX], textures[P_YELLOW_TEX], textures[P_GREEN_TEX] };

    for (size_t i{}; i < nPlayers; ++i) {
        double xPos{ std::get<0>(positions[i]) };
        double yPos{ std::get<1>(positions[i]) };
        Player* p = new Player{ xPos, yPos, 0, pTextures[i], textures[P_BACK_TEX], colors[i], shootBullet, &screen_w, &screen_h };

        addPlayer(p);
    }

}

void Manager::handleEvent(SDL_Event& event) {
	if (event.type == SDL_QUIT) {
		gameRunning = false;
    } else if (event.type == SDL_WINDOWEVENT) {
        if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
            screen_w = event.window.data1;
            screen_h = event.window.data2;
        }
    }
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
    ++playersAlive;
	players.push_back(p);
    this->addEntity(p);
    this->addCollisionable(p);
    pEvents.push_back(p->getEvents());
}

void Manager::addCollisionable(Entity* e) {
	collisionables.push_back(e);
}

void Manager::update() {
    /*
    std::cout << "Players: " << players.size() << "|\t";
    std::cout << "Entities: " << entities.size() << "|\t";
    std::cout << "Collisionables: " << collisionables.size() << "\n";
    */
    if (playersAlive == 1) {
        announceWinner();
        gameRunning = false;
    }

	this->handleKeyboard();

    updateDeltaTime();

    maybeSpawn();

    const size_t entitiesSize = entities.size();
    
	for (size_t i{}; i < entitiesSize; ++i) {
		entities.at(i)->simulate(deltaTime);
	}

    for (size_t i{}; i < collisionables.size(); ++i) {
        Entity* e0{ collisionables[i] };

        const Vector2<double> ePos{ e0->getPosOffsetApplied() };

        if (ePos.x < 0 || ePos.x > screen_w || ePos.y < 0 || ePos.y > screen_h) {
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
            } else if (id0 == 'p' && id1 == 's') {
                auto p{ dynamic_cast<Player*>(e0) };

                this->grabShooter(p, e1);
            } else if (id0 == 's' && id1 == 'p') {
                auto p{ dynamic_cast<Player*>(e1) };

                this->grabShooter(p, e0);
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
    --playersAlive;
    
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

void Manager::grabShooter(Player* p, Entity* powerup) {
    (this->toDestroy).push_back(powerup);

    p->addToEvents(SHOOTER);
    p->setShooterTime();
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

double Manager::newTimeToNextSpawn() {
    timeToNextSpawn = MIN_SPAWN_TIME + static_cast<double>(std::rand() / (static_cast<double>(RAND_MAX/(MAX_SPAWN_TIME - MIN_SPAWN_TIME))));

    return timeToNextSpawn;
}

void Manager::maybeSpawn() {
    timeToNextSpawn -= deltaTime;

    if (timeToNextSpawn <= 0) {
        newTimeToNextSpawn();

        const int randInt = std::rand();

        const double posX = static_cast<double>(std::rand() / (static_cast<double>(RAND_MAX / static_cast<double>(screen_w))));
        const double posY = static_cast<double>(std::rand() / (static_cast<double>(RAND_MAX / static_cast<double>(screen_h))));

        if (randInt < static_cast<double>(RAND_MAX) / 3.0) {
            Powerup* const bExplosion = new Powerup{ posX, posY, textures[B_EXPLOSION_TEX], 'x' };
            addCollisionable(bExplosion);
            addEntity(bExplosion);
        } else if (randInt < static_cast<double>(RAND_MAX) * (2.0/3.0)) {
            Powerup* const deadTouch = new Powerup{ posX, posY, textures[DEAD_TOUCH_TEX], 'd' };
            addCollisionable(deadTouch);
            addEntity(deadTouch);
        } else {
            Powerup* const shooter = new Powerup{ posX, posY, textures[SHOOTER_TEX], 's' };
            addCollisionable(shooter);
            addEntity(shooter);
        }
    }
}

void Manager::announceWinner() {
    const size_t playersSize{ players.size() };
    for (size_t i{}; playersSize > i; ++i) { 
        Player* p{ players.at(i) };

        if (*(p->getEvents()) & ALIVE) {
            switch (p->getColor()) {
            case Color::red:
                std::cout << "Red ";
                break;
            case Color::blue:
                std::cout << "Blue ";
                break;
            case Color::green:
                std::cout << "Green ";
                break;
            case Color::yellow:
                std::cout << "Yellow ";
                break;
            }

            std::cout << "player won!\n";
        }
    }
}
