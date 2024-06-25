sfml_include = /usr/local/Cellar/sfml/2.6.1/include
sfml_lib = /usr/local/Cellar/sfml/2.6.1/lib

calc: GraphingCalculator/*.cpp GraphingCalculator/*.h
	clang++ GraphingCalculator/*.cpp -o calc -I $(sfml_include) -L $(sfml_lib) -lsfml-graphics -lsfml-window -lsfml-system -std=c++17
