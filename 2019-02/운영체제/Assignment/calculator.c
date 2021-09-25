#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void* avg_handler(void* arg);
void* max_handler(void* arg);
void* min_handler(void* arg);

double avg;
int max;
int min;

typedef struct{
    int* numbers;
    int count;
}  SERIES;

int main(int argc, char* argv[]){
    pthread_t t_avg, t_max, t_min;
    SERIES numb;
    int i;

    if(argc < 2){
        printf("No Number is passed\n");
        exit(1);
    }

    numb.count = argc-1;
    numb.numbers = (int*)malloc(sizeof(int)*numb.count);

    for(i=0; i<numb.count; i++)
        numb.numbers[i] = atoi(argv[i+1]);
    
    if(pthread_create(&t_avg, NULL, avg_handler, (void*)&numb)!=0){
        printf("pthread_create() average error\n");
        exit(1);
    }
    if(pthread_create(&t_max, NULL, amx_handler, (void*)&numb)!=0){
        printf("pthread_create() maximum error\n");
        exit(1);
    }
    if(pthread_create(&t_min, NULL, min_handler, (void*)&numb)!=0){
        printf("pthread_create() minimum error\n");
        exit(1);
    }

    pthread_join(t_avg, NULL);
    pthread_join(t_max, NULL);
    pthread_join(t_min, NULL);

    printf("The average value is %f.\n", avg);
    printf("The maximum value is %d.\n", max);
    printf("The minimum value is %d.\n", min);

    return 0;
}

void* avg_handler(void* arg){
    SERIES numb = *(SERIES*)arg;
    int i;

    for(i=0; i<numb.count; i++)
        avg+=numb.numvers[i];
    
    avg /= numb.count;
}

void* max_handler(void* arg){
    SERIES numb = *(SERIES*)arg;
    int i;

    max = numb.numbers[0];

    for(i=0; i<numb.count; i++)
        if(numb.numbers[i]>max)
            max = numb.numbers[i];
}

void* min_handler(void* arg){
    SERIES numb = *(SERIES*)arg;
    int i;

    min = numb.numbers[0];

    for(i=0; i<numb.count; i++)
        if(numb.numbers[i]<max)
            min = numb.numbers[i];
}