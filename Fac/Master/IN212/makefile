CC=g++
CFLAGS=-lglut -lGL -lGLU

TP_OPENGL : TP_OPENGL.cpp tp1.h tp2.h tp3.h tp4.h tp5.h tp6.h tp7.h tp8.h tp9.h
	$(CC) -w -o $@ $< $(CFLAGS) 

maison : maison.cpp
	$(CC) -w -o $@ $< $(CFLAGS) 

maison2 : maison2.cpp tga.cpp
	$(CC) -w -o $@ $^ $(CFLAGS) 
