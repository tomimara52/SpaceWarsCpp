#include <SDL2/SDL.h>
#include <cstdint>

#include "InputHandler.h"
#include "Math.h"

void InputHandler::update() const {
	const uint8_t* kbdState{ SDL_GetKeyboardState(NULL) };

	Vector2<float> newDir = Vector2<float>{ 0, 0 };

	if (kbdState[SDL_SCANCODE_D]) {
		Vector2<float> right{ 1.0f, 0.0f };
		newDir += right;
	}

	if (kbdState[SDL_SCANCODE_A]) {
		Vector2<float> left{ -1.0f, 0.0f };
		newDir += left;
	}

	if (kbdState[SDL_SCANCODE_W]) {
		Vector2<float> up{ 0.0f, -1.0f };
		newDir += up;
	}

	if (kbdState[SDL_SCANCODE_S]) {
		Vector2<float> down{ 0.0f, 1.0f };
		newDir += down;
	}

	newDir.normalize();
	player.dir = newDir;
}
