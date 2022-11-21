//
// Created by Luyi Xiao on 11/19/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>


typedef struct counter{
    int value;
    pthread_mutex_t lock;
} counter_t;

void init(counter_t* c) {
    c-> value = 0;
    pthread_mutex_init(&c->lock, NULL);
}

void increment(counter_t* c) {
    pthread_mutex_lock(&c -> lock);
    c-> value ++;
    pthread_mutex_unlock(&c -> lock);
}

void decrement(counter_t* c) {
    pthread_mutex_lock(&c -> lock);
    c-> value --;
    pthread_mutex_unlock(&c -> lock);
}

int get(counter_t* c) {
    pthread_mutex_lock(&c -> lock);
    int i = c-> value;
    pthread_mutex_unlock(&c -> lock);

    return i;
}

void *threadFunction(void* args) {
    counter_t* c = (counter_t *) args;
    increment(c);
    return (void *) 1;
}

int main() {
    pthread_t p1, p2;
    counter_t* c  = malloc(sizeof(counter_t));
    init(c);
    struct timeval start, end;
    gettimeofday(&start, NULL);
    for (int i =0 ; i < 10000; i ++) {
        pthread_create(&p1, NULL, threadFunction, c);
        pthread_create(&p2, NULL, threadFunction, c);
        pthread_join(p1, NULL);
        pthread_join(p2, NULL);
    }
    gettimeofday(&end, NULL);

    printf("%ld\n", ((end.tv_sec * 1000000 + end.tv_usec)
                     - (start.tv_sec * 1000000 + start.tv_usec)));

    printf("%d\n", get(c));
    free(c);
    return 1;
};



