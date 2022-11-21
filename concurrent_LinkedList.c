//
// Created by Luyi Xiao on 11/20/22.
//
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

typedef struct node{
    int value;
    struct node *next;
    pthread_mutex_t lock;
} node_t;

typedef struct LinkedList {
    node_t *head;
    pthread_mutex_t glock;
} list_t ;

void init(list_t *l) {
    l -> head = NULL;
    pthread_mutex_init(&l->glock, NULL);
}
void insert(list_t *l, int val) {
    node_t * new_node = malloc(sizeof(node_t));
    new_node -> value = val;
    pthread_mutex_init(&new_node -> lock, NULL);
    pthread_mutex_lock(&l->glock);
    new_node -> next = l -> head;
    l -> head = new_node;
    pthread_mutex_unlock(&l -> glock);
}

int lookup(list_t *l, int val) {
    int res = -1;

    node_t* curr = l->head;
    node_t* curr_next = curr -> next;
    pthread_mutex_lock(&curr->lock);
    while (curr && curr_next) {
        pthread_mutex_lock(&curr_next->lock);
        pthread_mutex_unlock(&curr -> lock);
        if (curr->value == val) res = 0;
        curr = curr->next;
        curr_next = curr_next->next;
    }
    pthread_mutex_unlock(&curr->lock);
    if (curr->value == val) res = 0;
    return res;
}
