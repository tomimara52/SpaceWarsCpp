#include <SDL2/SDL.h>
#include <cstdint>

#include "Manager.h"
#include "Math.h"
#include "Constants.h"

Manager::Manager()
	: p1Events{} { }    

void Manager::handleInput() {
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
