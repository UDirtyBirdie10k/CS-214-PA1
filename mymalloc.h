#ifndef _mymalloc_h_
#define _mymalloc_h_

#include <stdlib.h>
#include <stdio.h>

#define MEMLENGTH 512

#define malloc(s) mymalloc(s, __FILE__, __LINE__);
#define free(p) free(p, __FILE__, __LINE__);

void *mymalloc(unsigned int size, char *FILE, int LINE);
void myfree(void *z, char *FILE, int LINE);

// helper functions
unsigned short using(unsigned char*);
unsigned short Width_Byte(unsigned char*);
unsigned short partSize(unsigned char*);
unsigned short SIZE(unsigned short size);
void setChunk(unsigned char* mem_Part, unsigned short using, unsigned short size);
void removeChunk(unsigned char* mem_Part);
void show_MEM();
void merge();

#endif