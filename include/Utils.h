#pragma once

#include <SDL2/SDL.h>

namespace utils {
	inline float hireTimeInSeconds() {
		float t = SDL_GetTicks();
		return t * 0.001f;
	}
}
