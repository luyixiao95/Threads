//
// Created by Luyi Xiao on 11/20/22.
//
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
typedef struct treeNode{
    int value;
    struct treeNode* left;
    struct  treeNode* right;
} treeNode_t;

typedef struct tree{
    treeNode_t *root;
    pthread_mutex_t lock;
} tree_t;
void init(int val, tree_t* t) {
    treeNode_t* root = malloc(sizeof(treeNode_t));
    t -> root = root;
}
int dfs_helper(treeNode_t *curr, int val) {
    if(curr == NULL) return -1;
    if(curr->value = val) return 0;
    dfs_helper(curr->left, val);
    dfs_helper(curr->right, val);
    return -1

}
int dfs(tree_t* t, int val) {
    int res = -1;
    treeNode_t * curr = t->root;
    pthread_mutex_lock(&t->lock);
    res = dfs_helper(curr, val);
    pthread_mutex_unlock(&t->lock);
    return res
}

