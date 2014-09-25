all : main

main : Wave.o main.o
	g++ -Wall -o main Wave.o main.o 
Wave.o : Wave.cpp
	g++ -Wall -o Wave.o -c Wave.cpp
main.o : main.cpp
	g++ -Wall -o main.o -c main.cpp
