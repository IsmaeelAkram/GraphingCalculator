#pragma once
#include "constants.h"
#include "point.h"
#include <SFML/Graphics.hpp>

sf::VertexArray render_x_axis();
sf::VertexArray render_y_axis();
void render_grid(sf::RenderWindow* window);