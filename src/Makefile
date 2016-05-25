OBJECTS = main.o painter.o field.o player.o game.o enemy.o creature.o
FLAGS = -c -lglut -lGL -Wall -pedantic
CC = g++

steal-n-run: $(OBJECTS)
	$(CC) $(OBJECTS) -o steal-n-run -lglut -lGL
main.o: main.cpp painter.hpp field.hpp
	$(CC) $(FLAGS) main.cpp
painter.o: painter.cpp painter.hpp
	$(CC) $(FLAGS) painter.cpp
field.o: field.cpp field.hpp painter.hpp enemy.hpp
	$(CC) $(FLAGS) field.cpp
player.o: creature.o player.cpp player.hpp field.hpp enemy.hpp
	$(CC) $(FLAGS) player.cpp
game.o: game.cpp game.hpp painter.hpp field.hpp player.hpp enemy.hpp
	$(CC) $(FLAGS) game.cpp
enemy.o: creature.o enemy.cpp enemy.hpp field.hpp
	$(CC) $(FLAGS) enemy.cpp
creature.o: creature.cpp creature.hpp field.hpp
	$(CC) $(FLAGS) creature.cpp
clean:
	rm -rf *.o steal-n-run ../level_map