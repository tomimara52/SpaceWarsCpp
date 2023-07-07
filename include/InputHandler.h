#pragma once
#include <SDL2/SDL.h>
#include <cstdint>

#include "Player.h"

class InputHandler {
public:
	InputHandler(Player& player)
		: player{ player } {}

	void update() const;
private:
	Player& player;
};
