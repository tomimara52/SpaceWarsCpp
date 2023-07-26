#include <tuple>

#include "Color.h"

std::tuple<unsigned int, unsigned int, unsigned int> getHexColor(Color color) {
    switch (color) {
    case Color::red:
        return { 255, 0, 0 };
    case Color::green:
        return { 0, 255, 0 };
    case Color::blue:
        return { 0, 0, 255 };
    case Color::yellow:
        return { 255, 255, 0 };
    }
}
