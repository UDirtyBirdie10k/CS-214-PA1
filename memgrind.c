#include "mymalloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define numIterations 50
#define numObjects 120


void run1(){

    struct timeval timeStart, timeEnd;
    double timeTotal = 0.0;

    for(int i = 0; i < numIterations; i++){

        gettimeofday(&timeStart, NULL);
        
        for(int j = 0; j < numObjects; j++){

            char* ptr = malloc(1);
            free(ptr);

        }

        gettimeofday(&timeEnd, NULL);

    }
    timeTotal += timeEnd.tv_usec - timeStart.tv_usec;

}

void run2(){

    struct timeval timeStart, timeEnd;
    double timeTotal = 0.0;
    char* array[numObjects];

    for(int i = 0; i < numIterations; i++){

        gettimeofday(&timeStart, NULL);
        
        for(int j = 0; j < numObjects; j++){

            array[j] = malloc(1);

        }
        for(int j = 0; j < numObjects; j++){

            free(array[j]);

        }

        gettimeofday(&timeEnd, NULL);
        timeTotal += timeEnd.tv_usec - timeStart.tv_usec;

    }



}

void run3(){

    struct timeval timeStart, timeEnd;
    double timeTotal = 0.0;
    char* array[numObjects];
    int allocatedObjects = 0;


    for(int i = 0; i < numIterations; i++){

        gettimeofday(&timeStart, NULL);
        
        for(int j = 0; j < numObjects; j++){
            
            int choice = rand() % 2;

            if (choice == 0 && allocatedObjects < numObjects) {

                array[allocatedObjects] = (char*)malloc(1);
                allocatedObjects++;
            } 
            else if (allocatedObjects > 0) {

                free(array[allocatedObjects]);
                --allocatedObjects;
            }   
        }
        for(int j = 0; j < allocatedObjects; j++){

            free(array[j]);

        }

        for(int i = 0; i < numIterations; i++){
            free(array[i]);
        }

        gettimeofday(&timeEnd, NULL);
        timeTotal += timeEnd.tv_usec - timeStart.tv_usec;

    }

}