OBJECTS = main.o painter.o field.o player.o game.o enemy.o
FLAGS = -c -lglut -lGL -Wall -pedantic
CC = g++

steal-n-run: $(OBJECTS)
	$(CC) $(OBJECTS) -o steal-n-run -lglut -lGL
main.o: main.cpp painter.hpp field.hpp
	$(CC) $(FLAGS) main.cpp
painter.o: painter.cpp painter.hpp
	$(CC) $(FLAGS) painter.cpp
field.o: field.cpp field.hpp painter.hpp
	$(CC) $(FLAGS) field.cpp
player.o: player.cpp player.hpp field.hpp
	$(CC) $(FLAGS) player.cpp
game.o: game.cpp game.hpp painter.hpp field.hpp player.hpp enemy.hpp
	$(CC) $(FLAGS) game.cpp
enemy.o: enemy.cpp enemy.hpp field.hpp
	$(CC) $(FLAGS) enemy.cpp
clean:
	rm -rf *.o steal-n-run
