CCX = clang++
CC = clang

CFLAGS += -O2
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
	${CCX} ${CXXFLAGS} src/main.c src/App.cpp src/Camera.cpp src/Grid.cpp src/Loader.cpp src/OpenGLGeo.cpp src/Shader.cpp src/ShaderManager.cpp -o sandbox ${LFLAGS}
