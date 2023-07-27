/* a piece of code that generates 3 sequences using singly linked lists and places 
a random number in all 3 of them. then, finds the random number and tells the user whether the lists should move
anti or clockwise several times to get them all align according to shared number. if so, also rearranges the sequences
and shows the final results.*/


#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef struct list {
    int number;
    struct list *next;
} LIST;

void list(LIST *front){
    LIST *tmp = front;
    do{
        printf("%d\t",tmp->number);
        tmp = tmp->next;
    } while(tmp != front);
    printf("\n");
}
void createList(LIST **front, LIST** rear,int random,int* visited1, int n, int m) {
     int i;
     int place = rand() % m;
    int *visited2 = (int*) calloc(n,sizeof(int)); 
	visited2[random] = 1;
     for(i=0;i<m;i++){
         LIST *tmp = (LIST *) malloc(sizeof(LIST));
         if(i==place){
             tmp->number = random;
         } else{
             do {
                 tmp->number = rand() % n;
             } while(visited1[tmp->number] >= 2 || visited2[tmp->number] != 0);
             visited1[tmp->number]++;
             visited2[tmp->number] = 1;
         }
         if(i==0){
             (*rear) = (*front) = tmp;
         } else {
             (*rear)->next = tmp;
             (*rear) = tmp;
             tmp->next = NULL;
         }
     }
      free(visited2);
     (*rear)->next = *front;
     list((*front));
}

void browse(LIST *front, int* visited){
    LIST *tmp = front;
    do{
        visited[tmp->number]++;
        tmp = tmp->next;
    }while(tmp != front);
}

int findPlace(LIST *front, int number,int list){
    LIST *tmp = front;
    int counter = 1;
    do{
        if(tmp->number == number){
            printf("Place in the list %d: %d\n",list,counter);
            return counter;
        }
        counter++;
        tmp = tmp->next;
    }while(tmp != front);
}

void sharedNumber(LIST *front1,LIST *front2,LIST *front3, int* visited, int sharednPlace[], int n){
    int i;
    for(i=0;i<n;i++){
        visited[i] = 0;
    }

    browse(front1,visited);
    browse(front2,visited);
    browse(front3,visited);

    for(i=0;i<n;i++){
        if(visited[i] == 3){
            sharednPlace[0] = i;
        }
    }
    printf("Shared number: %d\n",sharednPlace[0]);
    sharednPlace[1] = findPlace(front1,sharednPlace[0],1);
    sharednPlace[2] = findPlace(front2,sharednPlace[0],2);
    sharednPlace[3] = findPlace(front3,sharednPlace[0],3);
}


void rearrange(LIST **front, LIST **rear, int counter){
     int i;
     if(counter>0){  
       LIST *tmp;
      for(i=1;i<=count;i++){
        tmp = (*front);
        while(tmp->next != (*rear)){
            tmp = tmp->next;
        }
        (*rear) = tmp;
        (*front) = (*rear)->next;
        }
    } else if(counter<0){
        counter *= -1;
       for(i=1;i<=count;i++){
       *rear = *front;
       (*front) = (*front)->next;
     }
    }
     list(*front);
}

int movement(int place, int wanted, int m, int number){

    int tmp = place;
    int counter1 = 0;

    while(tmp != wanted){
        if(tmp == m){
            tmp = 0;
        }
        tmp++;
        counter1++;
    }

    if(counter1 == 0){
        printf("\nList %d is in the right order.",number);
        return 0;
    }

    int counter2 = m - counter1;

    if(counter1>counter2){
        printf("\nList %d should be moved anticlockwise %d time(s).",number,counter2);
        counter2 *= (-1);
        return counter2;
    } else{
        printf("\nList %d should be moved clockwise %d time(s).",number,counter1);
        return counter1;
    }
}

void freeList(LIST *front, int m){
    int i;
    LIST *tmp = front;
    for(i=0;i<m;i++){
        front = tmp->next;
        free(tmp);
        tmp = front;
    }
}



int main() {
	
    int m,n;

    do{
        printf("n: "); scanf("%d",&n);
        printf("m: "); scanf("%d",&m);
    } while(n<m); // so that every value occurs only once in every sequence.

    srand(time(NULL));
    int random = rand() % n; // the shared number which will be present in every sequence.
    LIST *front1=NULL,*front2=NULL,*front3=NULL,*rear1=NULL,*rear2=NULL,*rear3=NULL;
    int *visited = (int*) calloc(n,sizeof(int));
    visited[random] = 3;

    printf("List 1&2&3, respectively:\n");
    createList(&front1,&rear1,random,visited,n,m);
    createList(&front2,&rear2,random,visited,n,m);
    createList(&front3,&rear3,random,visited,n,m);

    printf("\n\n");

   int sharednPlace[4];
   sharedNumber(front1,front2,front3,visited,sharednPlace,n);

   int counter1,counter2;

   counter1 = movement(sharednPlace[2],sharednPlace[1],m,2);
   counter2 = movement(sharednPlace[3],sharednPlace[1],m,3);

    printf("\nRearranged lists: \n\n");
    list(front1);
    rearrange(&front2,&rear2,counter1);
    rearrange(&front3,&rear3,counter2);
       
	free(visited);
	freeList(front1,m);
	freeList(front2,m);
	freeList(front3,m);

    return 0;
}
