#pragma once

#include <cstdint>

class Manager {
public:
	Manager();

	void handleInput();

	void resetEvents();

	uint_fast8_t getP1Events();

	double updateDeltaTime();

	double getDeltaTime();
private:
	uint_fast8_t p1Events;
	double deltaTime;
	uint64_t prevTime;
	uint64_t prevPrevTime;
};
