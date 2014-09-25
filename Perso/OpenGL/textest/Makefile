SOURCES =	main.cpp \
		sdlglutils.cpp
OBJECTS	=	$(SOURCES:.cpp=.o)
TARGET	=	sdlgl_06_textures	
LIBS	=	$(shell sdl-config --libs) -lSDL_image -lGL -lGLU 

all: $(OBJECTS)
	g++ $(LIBS) -o $(TARGET) $(OBJECTS)

%o: %cpp
	g++ -o $@ -c $<

x: all
	./$(TARGET)

clean:
	rm -rf $(OBJECTS)

superclean : clean
	rm -rf $(TARGET)

