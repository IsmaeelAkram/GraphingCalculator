#pragma once
#include <cstdlib>
#include <string>
#include <stdio.h>
#include <regex>
#include "tinyexpr.h"
#include <SFML/Graphics.hpp>
#include "constants.h"
#include "point.h"

class Equation {
  public:
    std::string text;
    float compute_function(float x);
    sf::VertexArray render_function(int ord=0);
    sf::Color color;

    Equation(std::string text) {
        this->text = text;
    }
  private:
    sf::Color get_function_color(int ord);
    te_parser tep;
};