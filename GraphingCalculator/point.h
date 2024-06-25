#pragma once
#include <SFML/Graphics.hpp>
#include "constants.h"

struct point {
  float x;
  float y;
};
sf::Vector2f point_to_pixel(point p);
point pixel_to_point(sf::Vector2i px);


