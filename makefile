CC = clang
CFLAGS = -Wall -pedantic -std=c99
# DEPS = mol.h
LIBS=-lm # note: the l means library, m means math

# all: main
all: myprog 

clean:  
	rm -f *.o *.so myprog

libmol.so: mylib.o
	$(CC) mylib.o -shared -o libmol.so $(LIBS)
	
mylib.o:  mol.c mol.h
	$(CC) $(CFLAGS) -c mol.c -fPIC -o mylib.o

main.o:  test2.c mol.h
	$(CC) $(FLAGS) -c test2.c -o main.o 

myprog:  main.o libmol.so
	$(CC) main.o -L. -l mol -o myprog $(LIBS)
