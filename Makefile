SRC = src/*.cpp
INC = inc/*.hpp

TARGET = arcanoid

FLAGS = -std=c++17 -Wall -Wextra

all:
	@g++ $(SRC) $(FLAGS) -o $(TARGET) -I $(INC) `sdl2-config --cflags --libs` -lSDL2_image
