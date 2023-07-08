#include <SDL2/SDL.h>
#include <cstdint>

#include "Manager.h"
#include "Math.h"
#include "Constants.h"

Manager::Manager()
    : p1Events{}, deltaTime{}, prevTime{}, prevPrevTime{},
      gameRunning{ true } { }

void Manager::handleEvent(SDL_Event& event) {
	if (event.type == SDL_QUIT)
		gameRunning = false;
}

void Manager::handleKeyboard() {
	const uint_fast8_t* kbdState{ SDL_GetKeyboardState(NULL) };

	if (kbdState[SDL_SCANCODE_D]) {
		p1Events = p1Events | RIGHT;
	}

	if (kbdState[SDL_SCANCODE_A]) {
		p1Events = p1Events | LEFT;
	}

	if (kbdState[SDL_SCANCODE_W]) {
		p1Events = p1Events | UP;
	}

	if (kbdState[SDL_SCANCODE_S]) {
		p1Events = p1Events | DOWN;
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
