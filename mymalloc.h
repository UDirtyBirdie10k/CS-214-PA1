#ifndef _mymalloc_h_
#define _mymalloc_h_

#define MEMLENGTH 512

#define malloc(s) mymymalloc(s, __FILE__, __LINE__);
#define free(p) myfree(p, __FILE__, __LINE__);

void *mymalloc(unsigned int size, char *file, int line);
void myfree(void *ptr, char *file, int line);

#endif