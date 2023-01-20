CC = clang
CFLAGS = -Wall -pedantic -std=c99
# DEPS = mol.h
LIBS=-lm # note: the l means library, m means math

# all: main

main: main.o mol.o
	$(CC) $(CFLAGS) main.o mol.o -o main

test1: test1.o mol.o
	$(CC) mol.o test1.o -o test1 $(LIBS)

test1.o: test1.c mol.h # object file for test1.c  
	$(CC) $(CFLAGS) test1.c -c

mol.o: mol.c mol.h  # object file for mol.c
	$(CC) $(CFLAGS) mol.c -c

main.o: main.c mol.h
	$(CC) $(CFLAGS) main.c -c

clean:
	rm -f *.o *.so main