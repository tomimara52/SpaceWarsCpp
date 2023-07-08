#pragma once

#include <cstdint>

class Manager {
public:
	Manager();

	void handleInput();

	void resetEvents();

	uint_fast8_t getP1Events();
private:
	uint_fast8_t p1Events;
};
