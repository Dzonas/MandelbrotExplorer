# Mandelbrot Explorer
Mandelbrot Explorer is a program written in C++ using OpenGL.
You can use it to move around the fractal and zoom into it.

Controls:
- Q/E - zoom OUT/IN
- W/A/S/D - move UP/LEFT/DOWN/RIGHT
  
## Requirements
- CMake 3.13
- GPU supporting OpenGL 4.5

## Build
```
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

## Run
```
./bin/MandelbrotExplorer
```