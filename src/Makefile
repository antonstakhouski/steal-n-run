CPPFLAGS=-Wall -g
OBJECTS=main.o painter.o field.o player.o game.o
TARGET=steal-n-run
%.o: %.cpp
	g++ -c $(CPPFLAGS) -o $@ $<
$(TARGET): $(OBJECTS)
	g++ $(OBJECTS) -o $(TARGET) -g -lpthread -lglut -lGL
main.o: main.cpp painter.hpp field.hpp
painter.o: painter.cpp painter.hpp
field.o: field.cpp field.hpp painter.hpp
player.o: player.cpp player.hpp field.hpp
game.o: game.cpp game.hpp painter.hpp field.hpp player.hpp
