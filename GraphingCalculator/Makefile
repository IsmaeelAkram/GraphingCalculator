sfml_include = /usr/local/Cellar/sfml/2.6.1/include
sfml_lib = /usr/local/Cellar/sfml/2.6.1/lib

calc: *.cpp *.h
	clang++ *.cpp -o calc -I $(sfml_include) -L $(sfml_lib) -lsfml-graphics -lsfml-window -lsfml-system -std=c++17
