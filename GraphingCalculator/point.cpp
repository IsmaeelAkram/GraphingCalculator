#include "point.h"

sf::Vector2f point_to_pixel(point p) {
    sf::Vector2f pixel;
    pixel.x = (p.x * (QUADRANT_WIDTH / X_MAX)) + WINDOW_WIDTH / 2;
    pixel.y = (-p.y * (QUADRANT_HEIGHT / Y_MAX)) + WINDOW_HEIGHT / 2;
    return pixel;
}

point pixel_to_point(sf::Vector2i px) {
    point p;
    p.x = (px.x - WINDOW_WIDTH / 2) / (QUADRANT_WIDTH / X_MAX); // inverse 
    p.y = -(px.y - WINDOW_HEIGHT / 2) / (QUADRANT_HEIGHT / Y_MAX);
    return p;
}
