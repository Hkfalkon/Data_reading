# define C compiler & flags
CC = gcc
CFLAGS = -Wall -g
# define libraries to be linked (for example -lm)
LIB = 

# define sets of header source files and object files
SRC = main.c linkedlist.c data.c 
# OBJ is the same as SRC, just replace .c with .h
OBJ = $(SRC:.c=.o)
 

# the first target:
dict1: $(OBJ) 
	$(CC) $(CFLAGS) -o dict1 $(OBJ) $(LIB)

# the second target:
dict2: $(OBJ) 
	$(CC) $(CFLAGS) -o dict2 $(OBJ) $(LIB)


main.o: main.c data.h linkedlist.h

data.o: data.c data.h

linkedlist.o: linkedlist.c linkedlist.h data.h

clean:
	rm -f $(OBJ) dict1 dict2

