CC = g++
CFLAGS =
OBJ = main.o Parser.o
EXE = practica

all: $(OBJ)
	$(CC) -o $(EXE) $(OBJ) $(CFLAGS)

Parser: Parser.cc Parser.h
	$(CC) -c Parser.cc $(CFLAGS)
	
main: main.cc
	$(CC) -c main.cc $(CFLAGS)




.PHONY: clean

clean:
	rm -f $(EXE) $(OBJ)
