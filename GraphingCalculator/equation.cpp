#include "equation.h"

float Equation::compute_function(float x) {
    char x_str[16];
    sprintf_s(x_str, "%f", x);
    std::string substituted = std::regex_replace(this->text, std::regex("x"), x_str);
    return this->tep.evaluate(substituted);
}

sf::Color colors[5] = { sf::Color::Red, sf::Color::Cyan, sf::Color::Green, sf::Color::Magenta, sf::Color::Yellow };

sf::Color Equation::get_function_color(int ord) {
    return colors[ord % 5];
}

sf::VertexArray Equation::render_function(int ord) {
    sf::VertexArray vxa(sf::LineStrip, X_MAX * Y_MAX / RENDER_STEP);
    int i = 0;
    for (float x = -X_MAX; x <= X_MAX; x += RENDER_STEP) {
        float y = compute_function(x);
        point p{ x, y };

        vxa[i].position = point_to_pixel(p);
        this->color = get_function_color(ord);
        vxa[i].color = this->color;

        i++;
    }
    return vxa;
}
