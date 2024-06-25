#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <regex>
#include "tinyexpr.h"
#include "equation.h"
#include "grid.h"

int main(int argc, char* argv[])
{
    std::vector<Equation> eqs;
    const int functions_n = argc - 1;
    for(int i = 1; i <= functions_n; i++) {
      printf("equation found: %s\n", argv[i]);
      Equation equation((std::string)argv[i]); 
      eqs.push_back(equation);
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

    sf::VertexArray x_axis = render_x_axis();
    sf::VertexArray y_axis = render_y_axis();

    std::vector<sf::VertexArray> rendered_functions;
    for (int i = 0; i < eqs.size(); i++) {
        rendered_functions.push_back(eqs[i].render_function(i));
    }

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
            pixel_to_point(mouse_pos).x, eqs[0].compute_function(pixel_to_point(mouse_pos).x),
            eqs[0].text.c_str(),
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
        for (sf::VertexArray rendered_function : rendered_functions) {
            window.draw(rendered_function);
        }

        window.display();
    }

    return 0;
}
