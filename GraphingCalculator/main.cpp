#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <regex>
#include "tinyexpr.h"
#include "constants.h"
#include "equation.h"

#ifdef __APPLE__
#define sprintf_s sprintf
#endif

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

int main(int argc, char* argv[])
{
    const int functions_n = argc-1;
    Equation eqs[functions_n];
    for(int i = 1; i <= functions_n; i++) {
      printf("equation found: %s\n", argv[i]);
      Equation equation((std::string)argv[i]); 
      eqs[i-1] = equation;
    }

    sf::ContextSettings settings;
    //settings.antialiasingLevel = 8.0;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Graphing Calculator", sf::Style::Close, settings);
    window.setVerticalSyncEnabled(true);

    sf::Cursor cursor;
    cursor.loadFromSystem(sf::Cursor::Cross);
    window.setMouseCursor(cursor);

    sf::Event event;
    sf::Font roboto_mono;
    if (!roboto_mono.loadFromFile("RobotoMono-Regular.ttf")) {
        fprintf(stderr, "Could not load roboto font.\n");
        return 1;
    }
    
    sf::Text details_text;
    details_text.setFont(roboto_mono);
    details_text.setCharacterSize(24);
    details_text.setFillColor(sf::Color::White);
    details_text.setPosition(0.0f, 0.0f);

    sf::VertexArray function = render_function();
    sf::VertexArray x_axis = render_x_axis();
    sf::VertexArray y_axis = render_y_axis();

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            switch (event.type) {
            case(sf::Event::Closed):
                window.close();
                break;
            case(sf::Event::KeyPressed):
                if (event.key.code == sf::Keyboard::Q) {
                    window.close();
                }
                break;
            }
        }

        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
        char buf[1000];
        sprintf_s(buf, "screen: [%d, %d]\ntrace: (%.2f, %.2f)\n%s\nxMax: %d\nyMax: %d\nrenderStep: %.2f\ntraceStep: %.2f",
            mouse_pos.x, mouse_pos.y,
            pixel_to_point(mouse_pos).x, compute_function(pixel_to_point(mouse_pos).x),
            get_equation().c_str(),
            X_MAX,
            Y_MAX,
            RENDER_STEP,
            TRACE_STEP
            );
        details_text.setString(buf);

        window.clear();
        window.draw(details_text);
        window.draw(x_axis);
        window.draw(y_axis);
        render_grid(&window);
        window.draw(function);

        window.display();
    }

    return 0;
}
