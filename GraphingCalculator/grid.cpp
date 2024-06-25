#include "grid.h"

sf::VertexArray render_x_axis() {
    sf::VertexArray vxa(sf::LineStrip, 2);
    vxa.append(sf::Vertex(sf::Vector2f(0, WINDOW_HEIGHT / 2)));
    vxa.append(sf::Vertex(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT / 2)));
    return vxa;
}

sf::VertexArray render_y_axis() {
    sf::VertexArray vxa(sf::LineStrip, 2);
    vxa.append(sf::Vertex(sf::Vector2f(WINDOW_WIDTH / 2, 0)));
    vxa.append(sf::Vertex(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT)));
    return vxa;
}

void render_grid(sf::RenderWindow* window) {
    const int x_lines_n = (WINDOW_WIDTH) / (X_MAX * 2);
    sf::VertexArray x_lines[x_lines_n];
    for (int i = -X_MAX; i < x_lines_n; i += 1) {
        sf::VertexArray x_line(sf::LineStrip, 2);
        x_line[0].position = point_to_pixel(point{ (float)i,-WINDOW_HEIGHT });
        x_line[1].position = point_to_pixel(point{ (float)i,WINDOW_HEIGHT });
        x_line[0].color = sf::Color(255, 255, 255, 50);
        x_line[1].color = sf::Color(255, 255, 255, 50);
        window->draw(x_line);
    }

    const int y_lines_n = (WINDOW_HEIGHT) / (Y_MAX * 2);
    sf::VertexArray y_lines[y_lines_n];
    for (int i = -Y_MAX; i < y_lines_n; i += 1) {
        sf::VertexArray y_line(sf::LineStrip, 2);
        y_line[0].position = point_to_pixel(point{ -WINDOW_WIDTH,(float)i });
        y_line[1].position = point_to_pixel(point{ WINDOW_WIDTH,(float)i });
        y_line[0].color = sf::Color(255, 255, 255, 50);
        y_line[1].color = sf::Color(255, 255, 255, 50);
        window->draw(y_line);
    }
}