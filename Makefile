COMPILER = gcc
CFLAGS = -Wall -g
CFLAGS2 = -g

all: mymalloc Test1 Test2 Test3
.PHONY: clean

mymalloc.o: mymalloc.c mymalloc.h
	$(COMPILER) $(CFLAGS) -c mymalloc.c
