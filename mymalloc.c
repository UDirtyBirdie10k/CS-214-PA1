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
void show_MEM()
{

    // create a loop in order to go through the heap
    unsigned int i = 0;

    // while loop to preform the action to go through the heap
    while (i < MEMLENGTH)
    {

        // set a pointer to the piece of memory currently being investigated
        unsigned char *mem_Part = (unsigned char *)&curr_Part[i];

        // retrieve information about the current piece of memory
        printf("Index: %d, Address: %d, Bytes: %d, Size: %d\n", i, mem_Part, using(mem_Part), Width_Byte(mem_Part) + 1, partSize(mem_Part));

        // measure the amount of chunks in memory that currently have allocation
        if (partSize(mem_Part) > 0 || using(mem_Part))
        { // <---- shows if there is anything in memeory at this location or if the chunk is being used and adds to the counter [i]
            i += partSize(mem_Part);
        }
        else
        {
            i = MEMLENGTH
        } // sets the allocated chunks' index to the length in memory needed
    }
}

/// @brief
/// @param size
/// @param FILE
/// @param LINE
/// @return
void *mymalloc(unsigned int size, char *FILE, int LINE)
{

    unsigned int allocSize = size + 1;
    if (allocSize >= 64)
    {
        allocSize++; //<---- if allocSize >= 64 it is a two byte piece of data
    }

    // initialize looper
    unsigned int i = 0;

    while (i < MEMLENGTH)
    {
        unsigned char *mem_Part = (unsigned char *)&curr_Part[i];

        // make sure the memory is actually being used
        if (using(mem_Part) == 0) // reaches first unallocation
        {

            unsigned short Size = partSize(mem_Part); // check to see if you are you are at the end of memory or end of a chunk

            if (Size == 0) // end
            {
                if (i + allocSize <= MEMLENGTH) // see if memory is available
                {
                    setChunk(mem_Part, 1, allocSize);           // allocate current address in memory
                    setChunk(mem_Part + allocSize, 0, 0);       // set next to 0
                    return mem_Part + Width_Byte(mem_Part) + 1; // return the chunk
                }
                else
                {
                    break; // if no memory available leave the loop
                }
            }
            else
            {
                if (allocSize <= SIZE && allocSize > 0) // check to see if u can fit any bytes in the open block selected
                {
                    setChunk(mem_Part, 1, allocSize); // set memory address of current chunk without using the entire chunk if leftover bits
                    if (Size - allocSize > 0)
                    {
                        setChunk(mem_Part + allocSize, 0, Size - allocSize);
                    }
                    return mem_Part + Width_Byte(mem_Part) + 1; // return the chunk of memory
                }
            }
        }
        i += Size(mem_Part); // if no return we are still iterating
    }
    printf("OutOfMemory Error: Allocating more memory is unavailable %d, %s\n", line, file); // Data and loop break check
    return NULL;
}

void myfree(void *z, char *FILE, int LINE)
{

    if (pointer == NULL) // check to see if pointer is NULL
    {
        return;
    }
    unsigned short removed = 0;
    unsigned int i = 0;
    unsigned char *prevFree = NULL; // Take note of last free chunk of memory, if not then NULL

    // Loop to remove data from memory and join chunks that are free together
    while (i < MEMLENGTH)
    {
        unsigned char *mem_Part = (unsigned char *)&curr_Part[i]; // set out pointer to current chunk
        if (using(mem_Part) == 0)                                 // <-- check if the chunk is being used
        {
            unsigned short Size = partSize(mem_Part); // check size of the chunk
            if (Size == 0)
            {
                if (prevFree != NULL)
                {
                    setChunk(prevFree, 0, 0); // if the size of the chunk is NULL it is being used and if there
                }                             // is no memory after it we can set it to 0
                break;
            }
            else
            {
                if (mem_Part + 1 + Width_Byte(mem_Part) == pointer && removed == 0)
                {
                    printf("RedundantFree Error: Unable to deallocate memory which has already been deallocated %d, %s\n", line, file);
                    removed = 1;
                    break;
                }
                if (prevFree != NULL)
                {

                    //
                    int newSize = partSize(prevFree) + partSize(mem_Part);
                    setChunk(prevFree, 0, newSize);
                }
                i += partSize(mem_Part);
            }
            if (prevFree == NULL)
            {
                prevFree = mem_Part;
            }
        }
        else
        {
            if (mem_Part + 1 + Width_Byte(mem_Part) == pointer)
            {
                if (realSize(partSize(mem_Part)) != 0)
                {
                    removeChunk(mem_Part);
                }
                removed = 1;
            }
            else
            {
                prevFree = NULL;

                i += partSize(mem_Part);
            }
        }
    }
    if (removed == 0)
    {
        printf("Deallocation Error: Unable to deallocate with invalid pointer in line %d, %s\n", line, file)
    }
}
unsigned short using(unsigned char *mem_Part)
{
    return *mem_Part & 1;
}

unsigned short chunkSize(unsigned char *mem_Part)
{
    unsigned short byteLength = Width_Byte(mem_Part);
    if (byteLength == 0)
    {
        return (*mem_Part >> 2);
    }
    else
    {
        return (*(unsigned short *)mem_Part) >> 2;
    }
}
unsigned short realSize(unsigned short size)
{
    if (size < 64)
    {
        return size - 1;
    }
    else
    {
        return size - 2;
    }
}
void setChunk(unsigned char *mem_Part, unsigned short using, unsigned short size)
{
    if (size < 64)
    {
        *(mem_Part) = (size << 2) + using;
    }
    else
    {
        *((short *)mem_Part) = (size << 2) + using + 2;
    }
}
void removeChunk(unsigned char *mem_Part)
{
    setChunk(mem_Part, 0, partSize(mem_Part));
}
