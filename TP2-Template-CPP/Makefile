CC=g++
CFLAGS=-I. -Wall -Wextra -Werror -std=c++11 -pedantic -O2 -g
DEPS = rock.hpp
OBJ = rock.o main.o 

all: tp02 run

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

tp02: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

run: 
	./tp02 < input.txt

clean:
	rm -f *.o tp02