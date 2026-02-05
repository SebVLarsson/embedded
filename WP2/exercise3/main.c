#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//#### Constants #####
#define MAX 5


// ##### typedefs ####
typedef struct q{
    int number;
    struct q *next;
    struct q *prev;
} REGTYPE;


// ##### Function declarations #####
REGTYPE* random_list(void);
REGTYPE* add_first(REGTYPE* temp, int data);


//###### Main program #######
int main(int argc, char *argv[])
{
    int nr = 0;
    REGTYPE *act_post, *head = NULL;
    srand(time(0)); // Random seed
    head = random_list();
    act_post = head;

    // printing the randomly created list
    while (act_post != NULL) {
        printf("Post nr %d : %d\n" , nr++, act_post->number);
        act_post=act_post->next;
    }

    // reassigning the head address to act_post and sending the head aswell as nr into the function
    // if we wanted a new random number we could simply send the second parameter as (rand() %101)
    act_post = add_first(head, nr);

    //resetting nr to 0 so that we can loop over the list again to show the new head
    nr = 0;
    while (act_post != NULL) {
        printf("Post nr %d : %d\n" , nr++, act_post->number);
        act_post=act_post->next;
    }


    // --- Free the allocated memory ---
    while ((act_post = head) != NULL) {
        head = act_post->next;
        free(act_post);
    }
    return 0;
}
// ==== End of main ======================================

REGTYPE* random_list(void){
    // not sure what I need nr or i for here since we can declare i in the for loop
    int nr, i = 0;

    // initialize 3 structs, one current, one that we can save the top/head into and one old that we can save the current item to AFTER the iteration
    REGTYPE *top, *old, *item;

    // setting top to NULL so that we know if it's the first iteration or not for our creation loop
    top = NULL;
    
    /* 
    looping until MAX to create a node each iteration
    the idea is that each iteration we create a REGTYPE *item (node) and set it to its correct size with malloc
    we then set the number by rand
    set both next and prev to NULL since we don't know if we're working with head, tail, or a body node
    we then check, if the top is currently NULL, we know the current iteration is the top/head
    else we set the old->next to the newly created node, then set the current item->prev to old
    then we assign current node into old and go next iteration
    */

    for (i = 0; i < MAX; i++) {
        item = (REGTYPE*)malloc(sizeof(REGTYPE));
        item->number = rand() % 101; // % 100 + 1 to ensure we get a number between 1-100
        item->next = NULL;
        item->prev = NULL;

        if (top == NULL) {
            top = item;
        } else {
            old->next = item;
            item->prev = old;
        }
        old = item;
    }

    // return the head of the linked list
    return top;
}
//==========================================================

// insert at linked list 0/head position function
REGTYPE* add_first(REGTYPE* temp, int data){
    // create the new head as correct type and size
    REGTYPE *new_head = (REGTYPE*)malloc(sizeof(REGTYPE));

    // assign the new_head's number to the data
    new_head->number = data;
    // since it's the new head, set prev to NULL
    new_head->prev = NULL;
    //set the old head to new_head->next
    new_head->next = temp;
    // set the old heads prev to new_head
    temp->prev = new_head;

    // return the new head
    return new_head;
}