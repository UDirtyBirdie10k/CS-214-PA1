#ifndef _mymalloc_h_
#define _mymalloc_h_

#define MEMLENGTH 512

#define malloc(s) mymymalloc(s, __FILE__, __LINE__);
#define free(p) myfree(p, __FILE__, __LINE__);

void *mymalloc(unsigned int size, char *file, int line);
void myfree(void *ptr, char *file, int line);

// helper functions
unsigned short using(unsigned char*);
unsigned short Width_Byte(unsigned char*);
unsigned short partSize(unsigned char*);
unsigned short SIZE(unsigned short size);
void setChunk(unsigned char* mem_Part, unsigned short using, unsigned short size);
void removeChunk(unsigned char* mem_Part);
void show_MEM();

#endif