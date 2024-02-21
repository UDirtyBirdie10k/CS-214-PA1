COMPILER = gcc
CFLAGS = -Wall -g
CFLAGS2 = -g

all: mymalloc Test1 Test2 Test3
.PHONY: clean

mymalloc.o: mymalloc.c mymalloc.h
	$(COMPILER) $(CFLAGS) -c mymalloc.c

main.o: main.c mymalloc.h
	$(COMPILER) $(CFLAGS2) -c main.c

mymalloc: mymalloc.o main.o
	$(COMPILER) $(CFLAGS) -o mymalloc main.o mymalloc.o