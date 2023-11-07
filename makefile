CXX = g++
CXXFLAGS = -Wall -std=c++11 -I$(PROJECT_DIR)/src/Include -g
LIBS = -lmingw32 -lSDL2main -lSDL2 -L$(PROJECT_DIR)/src/lib -lSDL2_image -lSDL2_ttf -lSDL2_mixer

PROJECT_DIR = .

SOURCES = main.cpp window.cpp game.cpp button.cpp button_set.cpp shapes.cpp

all: $(SOURCES)
	$(CXX) $(CXXFLAGS) -o main $^ $(LIBS)
