CC=gcc
CCFLAGS=-std=c99 -Wall -Wextra -pedantic
CLFLAGS=

hmap.o: hmap.c hmap.h common.h
	$(CC) $(CCFLAGS) $< -c

#Removes all tildes ending files, objects codes and test executable
clean:
	rm -rf *~ *.o .*.swp  test
