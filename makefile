#objects to compile
OBJS = gameSoFar.cpp

#compiler flags that we wanna use
COMPILER_FLAGS = -g -Wall -Wextra -std=c++11


#all the libraries we wanna use
LINKER_FLAGS = -lSDL2 -lSDL2_image

#name of executable
OBJ_NAME = test

#ALL
all: bin/test

#CLEAN
clean:
	rm bin/test
	rm obj/*

#main
#bin/test: obj/gameSoFar.o obj/Character.o obj/Protagonist.o
#	g++ $(COMPILER_FLAGS) $(LINKER_FLAGS) -o bin/test obj/gameSoFar.o obj/Character.o obj/Protagonist.o
bin/test: obj/gameSoFar.o obj/Character.o obj/Antagonist.o obj/Projectile.o obj/Board.o
	g++ $(COMPILER_FLAGS) $(LINKER_FLAGS) -o bin/test obj/gameSoFar.o obj/Character.o obj/Antagonist.o obj/Projectile.o obj/Board.o

#compiling other files
obj/Character.o: include/Character.h
	g++ -c -o obj/Character.o src/Character.cpp

obj/Antagonist.o: include/Antagonist.h include/Character.h src/Antagonist.cpp
	g++ -c -o obj/Antagonist.o src/Antagonist.cpp

obj/Projectile.o: include/Projectile.h
	g++ -c -o obj/Projectile.o src/Projectile.cpp

obj/Board.o: include/Board.h src/Board.cpp
	g++ -c -o obj/Board.o src/Board.cpp

#obj/Protagonist.o: include/Protagonist.h
#	g++ -c -o obj/Protagonist.o src/Protagonist.cpp

#obj/gameSoFar.o: obj/Character.o obj/Protagonist
#	g++ -c -o obj/gameSoFar.cpp src/gameSoFar.cpp

obj/gameSoFar.o: obj/Character.o src/gameSoFar.cpp
	g++ -c -o obj/gameSoFar.o src/gameSoFar.cpp
