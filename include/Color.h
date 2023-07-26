#pragma once
#include <tuple>

enum Color {
    red,
    green,
    blue,
    yellow
};

std::tuple<unsigned int, unsigned int, unsigned int> getHexColor(Color color);
