#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <vector>

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

struct point {
    float x;
    float y;
};

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

std::string get_equation() {
    return "y=x^3";
}

float compute_function(float x) {
    return pow(x,3);
}

sf::VertexArray render_function() {
    sf::VertexArray vxa(sf::LineStrip, (X_MAX - X_MIN) / RENDER_STEP);
    int i = 0;
    for (float x = X_MIN; x <= X_MAX; x += RENDER_STEP) {
        float y = compute_function(x);
        point p{ x, y };

        vxa[i].position = point_to_pixel(p);
        vxa[i].color = sf::Color::Red;

        i++;
    }
    return vxa;
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
    
    sf::Text position_text;
    position_text.setFont(roboto_mono);
    position_text.setCharacterSize(24);
    position_text.setFillColor(sf::Color::White);

    sf::Text trace_text;
    trace_text.setFont(roboto_mono);
    trace_text.setStyle(sf::Text::Bold);
    trace_text.setCharacterSize(24);
    trace_text.setFillColor(sf::Color::White);
    trace_text.setPosition(0.0f, 32.0f);

    sf::Text equation_text;
    equation_text.setFont(roboto_mono);
    equation_text.setCharacterSize(24);
    equation_text.setFillColor(sf::Color::White);
    equation_text.setPosition(0.0f, 64.0f);

    std::string equation = get_equation();
    equation_text.setString((sf::String)equation);

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
        char position[24];
        sprintf_s(position, "screen: [%d, %d]", mouse_pos.x, mouse_pos.y);
        position_text.setString(position);

        char trace_step[100];
        sprintf_s(trace_step, "trace: (%.0f, %.0f)", pixel_to_point(mouse_pos).x, compute_function(3));
        trace_text.setString(trace_step);

        window.clear();
        window.draw(position_text);
        window.draw(trace_text); 
        window.draw(equation_text);
        window.draw(x_axis);
        window.draw(y_axis);
        window.draw(function);
        window.display();
    }

    return 0;
}