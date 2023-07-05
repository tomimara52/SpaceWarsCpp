FLAGS = -Wall -c -I include
HEADERS := $(wildcard src/*.h)
SOURCES := $(wildcard src/*.cpp)
LIBS = -lSDL2main -lSDL2 -lSDL2_image 

debug: $(HEADERS) $(SOURCES)
	g++ -g $(FLAGS) $(SOURCES) && g++ *.o -o bin/debug/main $(LIBS)

clean:
	rm -f *.o bin/debug/main bin/release/main
