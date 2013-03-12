CC=gcc
CCFLAGS=-std=c99 -Wall -Wextra -pedantic
CLFLAGS=

all: sstack.o squeue.o llist.o hmap.o 

sstack.o: sstack.c sstack.h common.h
	$(CC) $(CCFLAGS) $< -c

squeue.o: squeue.c squeue.h common.h
	$(CC) $(CCFLAGS) $< -c

llist.o: llist.c llist.h common.h
	$(CC) $(CCFLAGS) $< -c

hmap.o: hmap.c hmap.h common.h
	$(CC) $(CCFLAGS) $< -c

#Removes all tildes ending files, objects codes and test executable
clean:
	rm -rf *~ *.o .*.swp  test
