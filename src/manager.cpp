#include <SDL2/SDL.h>
#include <cstdint>

#include "Manager.h"
#include "Math.h"
#include "Constants.h"
#include "Player.h"

Manager::Manager(RenderWindow window)
	: gameRunning{ true }, window{ window }, entities{ }, players{ }, 
	  collisionables{ }, deltaTime{ }, prevTime{ }, prevPrevTime{ },
	  p1Events{ } { }

void Manager::handleEvent(SDL_Event& event) {
	if (event.type == SDL_QUIT)
		gameRunning = false;
}

void Manager::handleKeyboard() {
	const uint_fast8_t* kbdState{ SDL_GetKeyboardState(NULL) };

	if (kbdState[SDL_SCANCODE_W]) {
		p1Events = p1Events | FORWARD;
	}
}

void Manager::resetEvents() {
	p1Events = 0;
}

uint_fast8_t Manager::getP1Events() {
	return p1Events;
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
}

void Manager::addCollisionable(Entity* e) {
	collisionables.push_back(e);
}

void Manager::update() {
	this->handleKeyboard();

	(players[0])->setEvents(p1Events);

	for (Entity* e : entities) {
		e->simulate(deltaTime);
	}

	// handle collision in collisionables


	this->resetEvents();
}

void Manager::render() {

	window.clear();

	for (Entity* e : entities) {
		window.render(*e);
	}

	window.display();
}
