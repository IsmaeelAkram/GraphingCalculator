# GraphingCalculator

Written in C++ using SFML graphics and TinyExpr++ expression parsing.

## Settings
The settings are defined in `constants.h`:
```c
#define FONT_SIZE 20
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000
#define X_MAX 10
#define Y_MAX 10
#define RENDER_STEP 0.01
#define TRACE_STEP 0.1
#define THICKNESS 10
```

## Building
### Windows
Load the solution into Visual Studio, link dependencies, and build. If you get `unresolved external symbol` errors, try cleaning the build before building again.
### UNIX/Linux
The program can be built on UNIX/Linux systems using the Makefile.

Set the `sfml_include` and `sfml_lib` variables to the directories where SFML is installed on your system.

## Usage
Separate your equations using spaces
```
calc x x^2 sin(x) sin(x)*cos(x)
```

![screenshot](https://raw.githubusercontent.com/IsmaeelAkram/GraphingCalculator/master/screenshot.png)