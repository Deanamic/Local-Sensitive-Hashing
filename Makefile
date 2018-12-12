CC = g++
CFLAGS = -O2 -DLOCAL -g -fsanitize=undefined,address -Wall -Wshadow -std=c++14
OBJ = bin/main.o bin/parser.o bin/AhoCorasick.o
EXE = bin/LSH.exe

bin/LSH.exe: $(OBJ)
	$(CC) -o $(EXE) $(OBJ) $(CFLAGS)

bin/parser.o: src/Parser.cc inc/Parser.h
	$(CC) -o bin/parser.o -c src/Parser.cc $(CFLAGS) -I ./inc

bin/AhoCorasick.o: src/AhoCorasick.cc inc/AhoCorasick.h
	$(CC) -o bin/AhoCorasick.o -c src/AhoCorasick.cc $(CFLAGS) -I ./inc

bin/main.o: src/main.cc
	$(CC) -o bin/main.o -c src/main.cc $(CFLAGS) -I ./inc

.PHONY: clean

clean:
	rm -f $(EXE) $(OBJ)
