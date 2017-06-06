CC = g++ 
CFLAGS = -Wall -Werror -pedantic 

all: TextGenerator

TextGenerator: MarkovModel.o TextGenerator.o
	$(CC) -o TextGenerator TextGenerator.o MarkovModel.o $(CFLAGS)

TextGenerator.o: MarkovModel.hpp TextGenerator.cpp
	$(CC) -c TextGenerator.cpp $(CFLAGS)

MarkovModel.o: MarkovModel.hpp MarkovModel.cpp
	$(CC) -c MarkovModel.cpp $(CFLAGS)

clean:
	rm MarkovModel.o TextGenerator.o TextGenerator
