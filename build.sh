clang-format --style="{BasedOnStyle: Mozilla, IndentWidth: 4}" -i code/*.cpp code/*.h 
clang -Wall -pedantic -std=c++17 code/*.cpp -lm -lstdc++ -lGLEW -lGL -lSDL2 -o 3d-sandbox
