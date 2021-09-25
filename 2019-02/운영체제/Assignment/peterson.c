#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdbool.h>

_Bool flag[2];
int turn;

typedef struct timeval Timeval;
TimeVal sys_time;
TimeVal time_step[2];

void *process(void* n){
    int i;
    int j;

    i = *(int*)n;

    flag[i] = true;
    turn = 1-i;

    gettimeofday(time_stp+i, NULL);
    leav_time(time_stp[i], i, 0);
    while(flag[1-i]&&turn==1-i);

    gettimeofday(time_stp+i, NULL);
    leave_time(time_stp[i], i, 1);

    for(j=0; j<3; j++){
        gettimeofday(time_stp+i, NULL);
        leave_time(time+stp[i], i, 2);
        sleep(1);
    }

    gettimeofday(time_stp+i, NULL);
    leave_time(time_stp[i], i, 3);

    flag[i] = false;
}

void leave_time(TimeVal mark_t, int n, int mode){
    long rst_sec, rst_usec;
    rst_sec = mark_t.tv_sec - sys_time.tv_sec;
    rst_usec = mark_t.tv_usec - sys_time.tv_usec;
    
    if(rst_usec<0){
        rst_sec--;
        rst_usec += 1000000;
    }

    rst_usec /= 10000;

    switch(mode){
        case 0:
        printf("[%ld.%02ld] P%d is waiting\n", rst_sec, rst_usec, n);
        break;
        case 1:
        printf("[%ld.%02ld] P%d enters CS\n", rst_sec, rst_usec, n);
        break;
        case 2:
        printf("[%ld.%02ld] P%d is in CS\n", rst_sec, rst_usec, n);
        break;
        case 3:
        printf("[%ld.%02ld] P%d gets out of CS\n", rst_sec, rst_usec, n);
        break;
        default: printf("time stamp error\n");
    }
}

int main(void){
    pthread_t p0, t1;
    int zero = 0, one = 1;

    flag[0] = false;
    flag[1] = false;
    turn = 0;

    printf("<Peterson's Algorithm>\n");
    printf("Processes P0, P1 are executed in order\n");
    printf("Each process is in CS for 3 seconds\n\n");

    if(pthread_create(&p0, NULL, process, (void*)&zero)!=0){
        printf("pthread_create() p0 error\n");
        exit(1);
    }
    if(pthread_create(&p1m NULL, process, (void*)&one)!=0){
        printf("pthread_create() p1 error\n");
        exit(1);
    }
    if(pthread_join(p0, NULL)!=0){
        printf("pthread_join() p0 error\n");
        exit(1);
    }
    if(pthread_join(p1, NULL)!=0){
        printf("pthread_join() p1 error");
        exit(1);
    }

}