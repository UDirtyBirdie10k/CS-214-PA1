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
        
        for(int j = 0; j < 120; j++){

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
    char* array[120];

    for(int i = 0; i < numIterations; i++){

        gettimeofday(&timeStart, NULL);
        
        for(int j = 0; j < 120; j++){

            array[j] = malloc(1);

        }
        for(int j = 0; j < 120; j++){

            free(array[j]);

        }

        gettimeofday(&timeEnd, NULL);
        timeTotal += timeEnd.tv_usec - timeStart.tv_usec;

    }



}

//Randomly malloc and add 1 byte pointer to array or freeing a pointer until array is empty. 

void run3(){

    struct timeval timeStart, timeEnd;
    double timeTotal = 0.0;
    char* array[120];
    int allocatedObjects = 0;


    for(int i = 0; i < numIterations; i++){

        gettimeofday(&timeStart, NULL);
        
        for(int j = 0; j < 120; j++){
            
            int choice = rand() % 2;

            if (choice == 0 && allocatedObjects < 120) {

                array[allocatedObjects] = (char*)malloc(1);
                allocatedObjects++;
            } 
            else if (allocatedObjects > 0) {

                free(array[allocatedObjects - 1]);
                allocatedObjects--;
            }   
        }
        for(int j = 0; j < 120; j++){

            free(array[j]);

        }


        gettimeofday(&timeEnd, NULL);
        timeTotal += timeEnd.tv_usec - timeStart.tv_usec;

    }

}
//Malloc 120 1 byte pointers and free them backwards. 

void run4(){

    struct timeval timeStart, timeEnd;
    double timeTotal = 0.0;
    char* array[120];
    int allocatedObjects = 0;

    for(int i = 0; i < numIterations; i++){

        gettimeofday(&timeStart, NULL);
        
        for(int j = 0; j < 120; j++){
            
            array[j] = malloc(1);
            
        }

        for(int j = 119; j >= 0; j--){
            free(array[i]);
        }

        gettimeofday(&timeEnd, NULL);
        timeTotal += timeEnd.tv_usec - timeStart.tv_usec;

    }


}

//Choosing a randomlySized malloc of size 1 - 65 or freeing a pointer

void run5(){
    
    struct timeval timeStart, timeEnd;
    double timeTotal = 0.0;
    int totalMallocs = 0;
    int totalFrees = 0;
    char* array[numObjects];
    int allocatedObjects = 0;

    for (int i = 0; i < numIterations; i++) {
        gettimeofday(&timeStart, NULL);

        while (allocatedObjects < numObjects) {
            int choice = rand() % 2;
            if ((choice == 0 && totalMallocs < numObjects) || totalFrees >= allocatedObjects) {
                int size = (rand() % 64) + 1; 
                array[allocatedObjects++] = (char*)malloc(size);
                totalMallocs++;
            } else if (totalFrees < allocatedObjects) {
                free(array[totalFrees]);
                totalFrees++;
            }
        }

        for (int j = 0; j < allocatedObjects; j++) {
            free(array[j]);
        }
        allocatedObjects = 0;
        totalMallocs = 0;
        totalFrees = 0;

        gettimeofday(&timeEnd, NULL);

    }
}
