#!/bin/bash
echo "- Compiling Your Program....\n"
gcc calcu.c -o calcu -lSDL2main -lSDL2 -lSDL2_image
echo "- ***** Running Program ****\n"
./calcu
