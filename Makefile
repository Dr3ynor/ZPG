TARGET = main

CXX = g++

CXXFLAGS = -std=c++14 $(shell pkg-config --cflags opencv4)

LIBS = -lGL -lGLEW -lglfw $(shell pkg-config --libs opencv4) -lassimp # Use on Linux
#LIBS = -lGLEW -lglfw -framework OpenGL $(shell pkg-config --libs opencv4) -lassimp # Use on MacOS

SRCS = $(wildcard *.cpp)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS) 

.PHONY: clean
clean:
	rm -f $(TARGET)
