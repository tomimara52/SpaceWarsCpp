FLAGS = -std=c++20 -Wall -c -I include
HEADERS := $(wildcard include/*.h)
SOURCES := $(wildcard src/*.cpp)
LIBS = -lSDL2main -lSDL2 -lSDL2_image 

debug: $(HEADERS) $(SOURCES) 
	mkdir -p bin/debug && g++ -g $(FLAGS) $(SOURCES) && g++ *.o -o bin/debug/main $(LIBS)

release: $(HEADERS) $(SOURCES) 
	mkdir -p bin/release && g++ -O3 $(FLAGS) $(SOURCES) && g++ *.o -o bin/release/main $(LIBS)

clean:
	rm -f *.o bin/debug/main bin/release/main
