#pragma once

#include <SDL2/SDL.h> 
#include <cstdint>

class Manager {
public:
	Manager();

	void handleKeyboard();

	void handleEvent(SDL_Event&);

	void resetEvents();

	uint_fast8_t getP1Events();

	double updateDeltaTime();

	double getDeltaTime();

	bool isGameRunning();
private:
	uint_fast8_t p1Events;
	double deltaTime;
	uint64_t prevTime;
	uint64_t prevPrevTime;
	bool gameRunning;
};
