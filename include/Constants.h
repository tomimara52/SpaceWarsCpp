#pragma once

#include <cstdint>

const int SCREEN_W = 500;
const int SCREEN_H = 500;

const uint_fast8_t ALIVE =         0b00000001;
const uint_fast8_t FORWARD =       0b00000010;
const uint_fast8_t DEAD_TOUCH =    0b00000100;

const double ACCELERATION = 200.0;
const double MAX_SPEED = 200.0;
const double ROT_SPEED = 5.0;
const double FRICTION = 100.0;

const double PI = 3.14159265358979323846;
