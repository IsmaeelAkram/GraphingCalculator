#include <cstdlib>
#include <string>
#include <stdio.h>
#include <regex>
#include "tinyexpr.h"
#include <SFML/Graphics.hpp>
#include "constants.h"
#include "point.h"

#ifdef __APPLE__
#define sprintf_s sprintf
#endif


class Equation {
  public:
    std::string text;
    float compute_function(float x);
    sf::VertexArray render_function();

    Equation(std::string text) {
        this->text = text;
    }
  private:
    te_parser tep;
};

float Equation::compute_function(float x) {
    char x_str[16];
    sprintf_s(x_str, "%f", x);
    std::string substituted = std::regex_replace(this->text, std::regex("x"), x_str);
    return this->tep.evaluate(substituted);
}

sf::VertexArray Equation::render_function(){
    sf::VertexArray vxa(sf::LineStrip, X_MAX*Y_MAX / RENDER_STEP);
    int i = 0;
    for (float x = -X_MAX; x <= X_MAX; x += RENDER_STEP) {
        float y = compute_function(x);
        point p{ x, y };

        vxa[i].position = point_to_pixel(p);
        vxa[i].color = sf::Color::Red;

        i++;
    }
    return vxa;

}
