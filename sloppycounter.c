
// Created by Luyi Xiao on 11/19/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

int threadCount = 0;
typedef struct counter{
    int global;
    pthread_mutex_t glock;
    int local[10];
    pthread_mutex_t llock[10];
    int threshold;
} counter_t;

void init(counter_t* c, int threshold) {
    c-> global = 0;
    c-> threshold = threshold;
    pthread_mutex_init(&c->glock, NULL);
    for(int i =0 ; i < 10; i ++) {
        c->local[i] = 0;
        pthread_mutex_init(&c-> llock[i], NULL);
    }
}

void increment(counter_t* c, int threadID, int amt) {
    int cpu = threadID % 10;
    pthread_mutex_lock(&c -> llock[cpu]);

    c-> local[cpu] += amt;

    if (c -> local[cpu] >= c -> threshold) {
        pthread_mutex_lock(&c -> glock);
        c->global += c->local[cpu];
        pthread_mutex_unlock(&c->glock);
        c->local[cpu] = 0;

    }
    pthread_mutex_unlock(&c -> llock[cpu]);
}


int get(counter_t* c) {
    pthread_mutex_lock(&c -> glock);
    int i = c-> global;
    pthread_mutex_unlock(&c -> glock);
    return i;
}

void *threadFunction(void* args) {
    counter_t* c = (counter_t *) args;
    increment(c, threadCount, 1);
    return (void *) 1;
}

int main() {
    pthread_t p[10];
    counter_t* c  = malloc(sizeof(counter_t));
    init(c, 5);
    struct timeval start, end;
    gettimeofday(&start, NULL);
    for (int i =0 ; i < 2000; i ++) {
        for (int j= 0 ; j < 10; j ++) {
            pthread_create(&p[j], NULL, threadFunction, c);
            threadCount += 1;
        }
        for (int k = 0 ; k < 10; k ++) {
            pthread_join(p[k], NULL);
        }
    }
    gettimeofday(&end, NULL);

    printf("%ld\n", ((end.tv_sec * 1000000 + end.tv_usec)
                     - (start.tv_sec * 1000000 + start.tv_usec)));

    printf("%d\n", get(c));
    free(c);
    return 1;
};