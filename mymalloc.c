#include "mymalloc.h"
#include <stdio.h>
#include <stdlib.h>

static double memory[MEMLENGTH];
        //**GUIDE**\\
// 1.) Create a loop that goes throught the chunk of memory access its components and display them and find the index that memory is allocated up to

/*
-method to display the function to see what is going in within the set of memory 
-
-displays information about memory,[INDEX, ADDRESS, BYTES, SIZE]
*/
void show_MEM() {
    
    //create a loop in order to go through the heap 
    unsigned int i = 0;
    
    //while loop to preform the action to go through the heap
    while (i < MEMLENGTH){
        
        //set a pointer to the piece of memory currently being investigated
        unsigned char* mem_Part = (unsigned char*) &curr_Part[i];
        
        //retrieve information about the current piece of memory
        printf("Index: %d, Address: %d, Bytes: %d, Size: %d\n", i, mem_Part, using(mem_Part), Width_Byte(mem_Part) +1, partSize(mem_Part));
        
        //measure the amount of chunks in memory that currently have allocation
        if (partSize(mem_Part) > 0 || using(mem_Part)){ // <---- shows that if there is anything in memeory at this location or if the chunk is being used and adds to the counter [i] 
            i += partSize(mem_Part);
        }
        else
        {i = MEMLENGTH} //sets the allocated chunks' index to the length in memory needed
    }
}
/*
*/
void *mymalloc(unsigned int size, char *FILE, int LINE){

    unsigned int allocSize = size + 1;
    if (allocSize >= 64) {
        allocSize++;
    }

    //initialize looper
    unsigned char* mem_Part = (unsigned char*)&curr_Part[i];
    
    //make sure the memory is actually being used
    if ( using(mem_Part) == 0){

        unsigned short Size = partSize(mem_Part);

        if (Size == 0) {
            if (i + allocSize <= MEMLENGTH){
            setChunk(mem_Part, 1, allocSize);
            setChunk(mem_Part + allocSize, 0, 0);
            return mem_Part + Width_Byte(mem_Part) + 1;
            }else{
                break;
            }    
            }else{
                if (allocSize <= SIZE && allocSize > 0) {
                    setChunk(mem_Part, 1, allocSize);
                    if (Size - allocSize > 0) {
                        setChunk(mem_Part + allocSize, 0, Size - allocSize);
                    }
                    return mem_Part + Width_Byte(mem_Part) + 1;
                }
            }
        }
        i += Size(mem_Part);
    }
    printf("OutOfMemory Error: Allocating more memory is unavailable %d, %s\n", line, file);
    return NULL;
}

void myfree(void *z, char *FILE, int LINE){

    if (pointer == NULL) {
        return;
    }
    unsigned short removed = 0;
    unsigned int i = 0;
    unsigned char* prevFree = NULL;

    //

    while (i < MEMLENGTH) {
        unsigned char* mem_Part = (unsigned char*) &curr_Part[i];
        if (using(mem_Part) == 0){
            unsigned short Size = partSize(mem_Part);
            if (Size == 0) {
                if (prevFree != NULL) {
                    setChunk(prevFree, 0, 0);
                }
                break;
            } else {
                if (mem_Part + 1 + Width_Byte(mem_Part) == pointer && removed == 0) {
                    printf("RedundantFree Error: Unable to deallocate memory which has already been deallocated %d, %s\n", line, file);
                    removed = 1;
                    break;
                }
                if (prevFree != NULL) {
                    
                    //
                    int newSize = partSize(prevFree) + partSize(mem_Part);
                    setChunk(prevFree, 0, newSize);
                }
                i += partSize(mem_Part);
            }
            if (prevFree == NULL) {
                prevFree = mem_Part;
            }
        } else {
            if ( )
        }
    }

}