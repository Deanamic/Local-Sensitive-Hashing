CC = g++
CFLAGS = -O2 -DLOCAL -g -fsanitize=undefined,address -Wall -Wshadow -std=c++14
OBJ = bin/main.o bin/Parser.o bin/AhoCorasick.o bin/PolyHash.o bin/MinHash.o bin/Jaccard.o bin/JaccardAhoCorasick.o bin/LSHBanding.o bin/OnePermutationHash.o bin/LSHOPBanding.o
EXE = bin/LSH.exe

bin/LSH.exe: $(OBJ)
	$(CC) -o $(EXE) $(OBJ) $(CFLAGS)

bin/WordShuffler.exe: bin/WordShuffler.o bin/Parser.o
	$(CC) -o bin/WordShuffler.exe bin/Parser.o bin/WordShuffler.o $(CFLAGS)

bin/WordShuffler.o: src/WordShuffler.cc inc/Parser.h
	$(CC) -o bin/WordShuffler.o -c src/WordShuffler.cc $(CFLAGS) -I ./inc

bin/Parser.o: src/Parser.cc inc/Parser.h
	$(CC) -o bin/Parser.o -c src/Parser.cc $(CFLAGS) -I ./inc

bin/AhoCorasick.o: src/AhoCorasick.cc inc/AhoCorasick.h
	$(CC) -o bin/AhoCorasick.o -c src/AhoCorasick.cc $(CFLAGS) -I ./inc

bin/main.o: src/main.cc inc/MinHash.h inc/OnePermutationHash.h inc/Jaccard.h inc/AhoCorasick.h inc/Parser.h inc/LSHBanding.h inc/JaccardAhoCorasick.h
	$(CC) -o bin/main.o -c src/main.cc $(CFLAGS) -I ./inc

bin/PolyHash.o: src/PolyHash.cc inc/PolyHash.h
	$(CC) -o bin/PolyHash.o -c src/PolyHash.cc $(CFLAGS) -I ./inc

bin/OnePermutationHash.o: src/OnePermutationHash.cc inc/OnePermutationHash.h inc/PolyHash.h
	$(CC) -o bin/OnePermutationHash.o -c src/OnePermutationHash.cc $(CFLAGS) -I ./inc

bin/LSHOPBanding.o: src/LSHOPBanding.cc inc/LSHOPBanding.h inc/OnePermutationHash.h
	$(CC) -o bin/LSHOPBanding.o -c src/LSHOPBanding.cc $(CFLAGS) -I ./inc

bin/MinHash.o: src/MinHash.cc inc/MinHash.h inc/PolyHash.h
	$(CC) -o bin/MinHash.o -c src/MinHash.cc $(CFLAGS) -I ./inc

bin/LSHBanding.o: src/LSHBanding.cc inc/LSHBanding.h inc/MinHash.h
	$(CC) -o bin/LSHBanding.o -c src/LSHBanding.cc $(CFLAGS) -I ./inc

bin/Jaccard.o: src/Jaccard.cc inc/Jaccard.h
	$(CC) -o bin/Jaccard.o -c src/Jaccard.cc $(CFLAGS) -I ./inc

bin/JaccardAhoCorasick.o: src/JaccardAhoCorasick.cc inc/JaccardAhoCorasick.h inc/AhoCorasick.h
	$(CC) -o bin/JaccardAhoCorasick.o -c src/JaccardAhoCorasick.cc $(CFLAGS) -I ./inc
.PHONY: clean

clean:
	rm -f $(EXE) $(OBJ)
