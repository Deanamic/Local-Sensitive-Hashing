CC = g++
CFLAGS = -O2 -DLOCAL -g -fsanitize=undefined,address -Wall -Wshadow -std=c++14
OBJ = bin/main.o bin/Parser.o bin/AhoCorasick.o bin/PolyHash.o bin/MinHash.o bin/Jaccard.o bin/JaccardAhoCorasick.o bin/LSHBanding.o bin/OnePermutationHash.o
EXE = bin/LSH.exe

bin/LSH.exe: $(OBJ)
	$(CC) -o $(EXE) $(OBJ) $(CFLAGS)

bin/Parser.o: src/Parser.cc inc/Parser.h
	$(CC) -o bin/Parser.o -c src/Parser.cc $(CFLAGS) -I ./inc

bin/AhoCorasick.o: src/AhoCorasick.cc inc/AhoCorasick.h
	$(CC) -o bin/AhoCorasick.o -c src/AhoCorasick.cc $(CFLAGS) -I ./inc

bin/main.o: src/main.cc bin/MinHash.o bin/OnePermutationHash.o bin/Jaccard.o bin/AhoCorasick.o bin/Parser.o bin/LSHBanding.o bin/JaccardAhoCorasick.o
	$(CC) -o bin/main.o -c src/main.cc $(CFLAGS) -I ./inc

bin/PolyHash.o: src/PolyHash.cc inc/PolyHash.h
	$(CC) -o bin/PolyHash.o -c src/PolyHash.cc $(CFLAGS) -I ./inc

bin/OnePermutationHash.o: src/OnePermutationHash.cc inc/OnePermutationHash.h bin/PolyHash.o
	$(CC) -o bin/OnePermutationHash.o -c src/OnePermutationHash.cc $(CFLAGS) -I ./inc

bin/MinHash.o: src/MinHash.cc inc/MinHash.h inc/PolyHash.h
	$(CC) -o bin/MinHash.o -c src/MinHash.cc $(CFLAGS) -I ./inc

bin/LSHBanding.o: src/LSHBanding.cc inc/LSHBanding.h bin/MinHash.o
	$(CC) -o bin/LSHBanding.o -c src/LSHBanding.cc $(CFLAGS) -I ./inc

bin/Jaccard.o: src/Jaccard.cc inc/Jaccard.h
	$(CC) -o bin/Jaccard.o -c src/Jaccard.cc $(CFLAGS) -I ./inc

bin/JaccardAhoCorasick.o: src/JaccardAhoCorasick.cc inc/JaccardAhoCorasick.h bin/AhoCorasick.o
	$(CC) -o bin/JaccardAhoCorasick.o -c src/JaccardAhoCorasick.cc $(CFLAGS) -I ./inc
.PHONY: clean

clean:
	rm -f $(EXE) $(OBJ)
