#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000
#define QUADRANT_WIDTH WINDOW_WIDTH/2
#define QUADRANT_HEIGHT WINDOW_HEIGHT/2
#define X_MIN -10
#define X_MAX 10
#define Y_MIN -10
#define Y_MAX 10
#define RENDER_STEP 0.01
#define THICKNESS 10

std::string get_equation() {
    return "y=x^2";
}

float point_to_pixel(float p) {
    return p * WINDOW_WIDTH / 5;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Graphing Calculator");
    window.setVerticalSyncEnabled(true);
    sf::Event event;

    sf::Font roboto_mono;
    if (!roboto_mono.loadFromFile("C:\\Users\\Chimera\\source\\repos\\GraphingCalculator\\x64\\Debug\\RobotoMono-Regular.ttf")) {
        fprintf(stderr, "Could not load roboto font.\n");
        return 1;
    }
    sf::Text equation_text;
    equation_text.setFont(roboto_mono);
    equation_text.setCharacterSize(24);
    equation_text.setFillColor(sf::Color::White);
    equation_text.setPosition(0.0f, WINDOW_HEIGHT-32.0f);

    sf::Text position_text;
    position_text.setFont(roboto_mono);
    position_text.setCharacterSize(24);
    position_text.setFillColor(sf::Color::White);

    std::string equation = get_equation();
    equation_text.setString((sf::String)equation);

    sf::VertexArray function(sf::LineStrip, (X_MAX - X_MIN) / RENDER_STEP);
    int i = 0;
    for (float x = X_MIN; x <= X_MAX; x += RENDER_STEP) {
        float y = pow(x, 2);
        float x_onscreen = (x * (QUADRANT_WIDTH / X_MAX)) + WINDOW_WIDTH / 2;
        float y_onscreen = (-y * (QUADRANT_HEIGHT / Y_MAX)) + WINDOW_HEIGHT / 2;

        function[i].position = sf::Vector2f(x_onscreen, y_onscreen);
        function[i].color = sf::Color::Red;

        i++;
    }

    sf::VertexArray x_line(sf::LineStrip, 2);
    x_line.append(sf::Vertex(sf::Vector2f(0, WINDOW_HEIGHT / 2)));
    x_line.append(sf::Vertex(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT / 2)));

    sf::VertexArray y_line(sf::LineStrip, 2);
    y_line.append(sf::Vertex(sf::Vector2f(WINDOW_WIDTH / 2, 0)));
    y_line.append(sf::Vertex(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT)));

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            switch (event.type) {
            case(sf::Event::Closed):
                window.close();
                break;
            case(sf::Event::KeyPressed):
                if(event.key.code == sf::Keyboard::Q){
                    window.close();
                }
                break;
            }
        }
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
        char position[16];
        sprintf_s(position, "[%d, %d]", mouse_pos.x, mouse_pos.y);
        position_text.setString(position);

        // clear with black color
        window.clear();

        // draw here
        window.draw(equation_text);
        window.draw(position_text);
        window.draw(x_line);
        window.draw(y_line);
        window.draw(function);

        // display the current frame
        window.display();
    }

    return 0;
}