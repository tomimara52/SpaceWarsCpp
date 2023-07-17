#include <SDL2/SDL.h>
#include <cstdint>

#include "Manager.h"
#include "Math.h"
#include "Constants.h"
#include "Player.h"

Manager::Manager(RenderWindow window)
	: gameRunning{ true }, window{ window }, entities{ }, players{ }, 
	  collisionables{ }, deltaTime{ }, prevTime{ }, prevPrevTime{ },
	  pEvents{ } { }

void Manager::handleEvent(SDL_Event& event) {
	if (event.type == SDL_QUIT)
		gameRunning = false;
}

void Manager::handleKeyboard() {
    size_t n_players = players.size();
	const uint8_t* kbdState{ SDL_GetKeyboardState(NULL) };

    if (n_players >= 1) {
        if (kbdState[SDL_SCANCODE_W]) {
            pEvents[0] = pEvents[0] | FORWARD;
        } else {
            pEvents[0] = pEvents[0] & (~FORWARD);
        }
    }

    if (n_players >= 2) {
        if (kbdState[SDL_SCANCODE_T]) {
            pEvents[1] = pEvents[1] | FORWARD;
        } else {
            pEvents[1] = pEvents[1] & (~FORWARD);
        }
    }

    if (n_players >= 3) {
        if (kbdState[SDL_SCANCODE_U]) {
            pEvents[2] = pEvents[2] | FORWARD;
        } else {
            pEvents[2] = pEvents[2] & (~FORWARD);
        }
    }

    if (n_players >= 4) {
        if (kbdState[SDL_SCANCODE_P]) {
            pEvents[3] = pEvents[3] | FORWARD;
        } else {
            pEvents[3] = pEvents[3] & (~FORWARD);
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
    pEvents.push_back(0);
}

void Manager::addCollisionable(Entity* e) {
	collisionables.push_back(e);
}

void Manager::update() {
	this->handleKeyboard();
	
    for (size_t i{}; i < players.size(); ++i) {
        (players[i])->setEvents(pEvents[i]);
    }

	for (Entity* e : entities) {
		e->simulate(deltaTime);
	}

    for (size_t i{}; i < collisionables.size(); ++i) {
        Entity* e0{ collisionables[i] };
        for (size_t j{ i+1 }; j < collisionables.size(); ++j) {
            Entity* e1{ collisionables[j] };
            if (e0->collides(e1)) {
                std::cout << "COLLISION\n";
            }
        }
    }

	//this->resetEvents();
}

void Manager::render() {

	window.clear();

	for (Entity* e : entities) {
		e->render(window.getRenderer());	
	}

	window.display();
}
