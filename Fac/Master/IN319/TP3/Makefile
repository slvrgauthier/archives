CXXFLAGS      = -O2 -Wall 
LFLAGS        = 
LIBS          = -L/usr/X11R6/lib -lm -lpthread -lX11
INCPATH       = -I../cimg -I.

all: icp 

icp: mesh.o icp.o
	g++ $(LFLAGS) -o icp mesh.o icp.o $(LIBS)

icp.o: icp.cpp
	gcc -c $(CXXFLAGS) $(INCPATH) -o icp.o icp.cpp

mesh.o: mesh.cpp
	gcc -c $(CXXFLAGS) $(INCPATH) -o mesh.o mesh.cpp

clean:
	rm icp.o mesh.o

