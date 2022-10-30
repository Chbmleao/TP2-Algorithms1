CC=g++
CFLAGS=-I. -Wall -Wextra -Werror -std=c++11 -pedantic -O2 -g
DEPS = rock.hpp
OBJ = rock.o main.o 

all: main run

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

run: 
	./main

clean:
	rm -f *.o main