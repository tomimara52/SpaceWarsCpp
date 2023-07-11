#pragma once

#include <cstdint>

const uint8_t FORWARD =         0b00000001;
const uint8_t STOP_FORWARD =    0b00000010;
const uint8_t RESET_VEL =       0b00000100;

const double ACCELERATION = 80.0;
const double MIN_SPEED = 40.0;
const double MAX_SPEED = 200.0;
const double ROT_SPEED = 5.0;
const double FRICTION = 50.0;
