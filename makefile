CC = clang
CFLAGS = -Wall -pedantic -std=c99
# DEPS = mol.h
LIBS=-lm # note: the l means library, m means math

# all: main
all: myprog 

clean:  
	rm -f *.o *.so myprog


# libmol.so: mylibmol.o
# 	$(CC) mylibmol.o -shared -o libmol.so

libmol.so: mylib.o
	$(CC) mylib.o -shared -o libmol.so $(LIBS)
	
mylib.o:  mol.c mol.h
	$(CC) $(CFLAGS) -c mol.c -fPIC -o mylib.o

main.o:  main.c mol.h
	$(CC) $(FLAGS) -c main.c -o main.o 

myprog:  main.o libmol.so
	$(CC) main.o -L. -l mol -o myprog $(LIBS)


# mylibmol.o:  mol.c mol.h
# 	$(CC) $(CFLAGS) -c mol.c -fPIC -o mylibmol.o

# myprog:  main.o libmol.so
# 	$(CC) main.o -L. -lmylibmol -o myprog $(LIBS)


# main: main.o mol.o
# 	$(CC) $(CFLAGS) main.o mol.o -o main $(LIBS)

# test1: test1.o mol.o
# 	$(CC) mol.o test1.o -o test1me $(LIBS)

# test1.o: test1.c mol.h # object file for test1.c  
# 	$(CC) $(CFLAGS) test1.c -c

# test2: test2.o mol.o
# 	$(CC) mol.o test2.o -o test2me $(LIBS)

# test2.o: test2.c mol.h # object file for test1.c  
# 	$(CC) $(CFLAGS) test2.c -c	

# test3: test3.o mol.o
# 	$(CC) mol.o test3.o -o test3me $(LIBS)

# test3.o: test3.c mol.h # object file for test1.c  
# 	$(CC) $(CFLAGS) test3.c -c

# mol.o: mol.c mol.h  # object file for mol.c
# 	$(CC) $(CFLAGS) mol.c -c


# main.o: main.c mol.h
# 	$(CC) $(CFLAGS) main.c -c


# clean:
# 	rm -f *.o *.so main