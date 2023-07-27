/* creates a random binary tree and the user tries to drop the nodes by entering 
a value bigger than their own value. the tree gets rearranged proper to binary tree
structure if a node falls off. */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node{
    int data;
    int value;
    // two variables to keep information of the actual value given
    // by the random number generator and its decreased value if node
    // gets hit by a 'rock'.
    struct node *left;
    struct node *right;
}NODE;

typedef struct stack{
     int data;
     struct stack* prev;
}STACK;

 NODE* newNode(int num){
     // create a simple new node.
     NODE* new =(NODE*)malloc(sizeof(NODE));
     new->data = new->value = num;
     new->left = NULL;
     new->right = NULL;
     return new;
 }

 NODE* insert(NODE* root, int num){
     if(root == NULL){
         return newNode(num); // implement none.
     }
     // if there's a root, find a suitable place for the new value.
     if(num < root->data){
         root->left = insert(root->left, num);
     } else if(num > root->data){
         root->right = insert(root->right, num);
     }
     return root;
 }


NODE* search(NODE* root, int num, int p){
     // search if the given number is present in the tree.
     if(root == NULL || root->data == num){
         if(root != NULL){
             root->value = root->value - p;
         }
         return root;
     }
     else if(root->data < num){
          return search(root->right, num, p);
     }
     return search(root->left, num, p);
 }

 STACK* push(STACK* latest, int fallen){
    // push the fallen node to the stack.
         STACK *new = (STACK*)malloc(sizeof(STACK));
         if(latest == NULL){
             new->prev = NULL;
         }
         new->data = fallen;
         new->prev = latest;
         return new;
 }

 NODE * min(NODE* node){
     // finds the min value on the right side of the subtree
     // which is actually max valued element compared on the left side.
       NODE* tmp = node;
       while(tmp && tmp->left != NULL){
           tmp = tmp->left;
       }
       return tmp;
 }

 NODE* deleteRoot(NODE* root, int fallen){
    // delete the fallen node.
     if (root == NULL){
         return root;
     }
     if(root->data > fallen){
         root->left = deleteRoot(root->left, fallen);
     } else if(root->data < fallen){
         root->right = deleteRoot(root->right, fallen);
     } else {
         NODE *tmp;
         if(root->left == NULL){
             tmp = root->right;
             free(root);
             return tmp;
         } else if(root->right == NULL){
             tmp = root->left;
             free(root);
             return tmp;
         }
         tmp = min(root->right);
         root->data = tmp->data;
         root->value = tmp->value;
         root->right = deleteRoot(root->right, tmp->data);
     }
     return root;
 }
int level(NODE* root) {
    // find the max level no regards to side of it.
    if (root == NULL) {
        return -1;
    } else {
        int leftLevel = level(root->left);
        int rightLevel = level(root->right);

        if (leftLevel > rightLevel) {
            return (leftLevel + 1);
        } else {
            return (rightLevel + 1);
        }
    }
}

void tree(NODE* root,int maxLevel){
    int i;
    printf("%d",root->data); printf("[%d]",root->value);
    if(root->left != NULL){
        printf("-L->");
        tree(root->left, maxLevel);
    }
    if(root->right != NULL){
        printf("\n");
        for(i = level(root); i < maxLevel; i++){
            printf("        ");
        }
        printf("    -R->");
        tree(root->right, maxLevel);
    }
}


int pop(STACK** latest) {
    int res;
    STACK* tmp;
    if (*latest == NULL) {
        return -1;
    } else {
        tmp = *latest;
        res = tmp->data;
        *latest = tmp->prev;
        free(tmp);
        return res;
    }
}

void popAll(STACK** latest) {
    if (*latest != NULL) {
        int data = pop(latest);
        popAll(latest);
        if(data != -1){
            printf("%d ", data);
        }
    }
}


int main() {

    int m, n;
    do{
        printf("enter the n value: ");
        scanf("%d", &n);
        printf("enter the m value: ");
        scanf("%d", &m);
    }while(m>n);
    // getting n and m numbers from the user.

    NODE *root = NULL;
    srand(time(NULL)); // initializing random seed.
    int i, random;
    int *visited = (int *) calloc(n, sizeof(int));

    // create the tree.
    for (i = 0; i < m; i++) {
        do {
            random = (rand() % n) + 1;
        } while (visited[random] == 1);
        visited[random]++;
        // use a visited array to make sure generated number isn't generated before.
        root = insert(root, random);
    }
    free(visited);



    int k, p;
    NODE *tmp = root;
    STACK *latest = NULL;
    while(root != NULL){
        // print tree.
        printf("\ntree:\n");
        tree(root,level(root));

    printf("\nenter the k number: ");
    scanf("%d", &k);
    printf("enter the p number: ");
    scanf("%d", &p);

    tmp = search(root, k, p);
    if (tmp == NULL) {
        // notify the user if entered number is not present in the tree.
        printf("\nentered k number is not present in the tree.");
    } else {
         if(tmp->value <= 0){ // check if the value of the node is equal to or below zero.
          latest = push(latest,k);
          root = deleteRoot(root,k);
         }
    }
    }
    printf("\n\nstack:\n");
    popAll(&latest);
    return 0;
}
