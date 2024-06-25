sfml_include = /usr/local/Cellar/sfml/2.6.1/include
sfml_lib = /usr/local/Cellar/sfml/2.6.1/lib

calc: main.cpp grid.cpp equation.cpp point.cpp constants.h grid.h equation.h point.h 
	clang++ main.cpp grid.cpp equation.cpp point.cpp tinyexpr.cpp -o calc -include tinyexpr.h -I $(sfml_include) -L $(sfml_lib) -lsfml-graphics -lsfml-window -lsfml-system -std=c++17
