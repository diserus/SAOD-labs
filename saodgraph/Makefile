all: compile link
	
compile:
	g++ main.cpp -Isrc/include -c main.cpp

link:
	g++ main.o -o main -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system