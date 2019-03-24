CCX = clang++
CC = clang

CFLAGS += -O2
CFLAGS += -c
CFLAGS += --std=c11
CFLAGS += -Isrc/

CXXFLAGS += -O2
CXXFLAGS += --std=c++17
CXXFLAGS += -Isrc/

LFLAGS += -lSDL2
LFLAGS += -lGL
LFLAGS += -lGLEW
LFLAGS += -lm

all:
	${CC} ${CFLAGS} src/sandbox.c -o sandbox.o
	${CCX} ${CXXFLAGS} src/sandbox.c src/camera.c src/main.cpp src/App.cpp src/Grid.cpp src/Loader.cpp src/OpenGLGeo.cpp src/Shader.cpp src/ShaderManager.cpp -o sandbox ${LFLAGS}
	rm sandbox.o
