
cmake_minimum_required(VERSION 3.10)
project(MySDLGame C)

# Find the SDL2 package on the system
find_package(SDL2 REQUIRED)

# If you use SDL2_image, find it too
find_package(SDL2_image REQUIRED)

# Define your executable name and source file (gcc main.c -o main)
add_executable(calcu calcu.c)

# Link the libraries (-lSDL2main -lSDL2 -lSDL2_image)
target_link_libraries(calcu PRIVATE SDL2::SDL2main SDL2::SDL2 SDL2_image::SDL2_image)
