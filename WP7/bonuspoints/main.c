#include <stdio.h> // io ops
#include <stdlib.h> // malloc
#include <ctype.h> // for atoi

// make our LL data structure struct
typedef struct linked_list{
    long value; // our fibonacci number
    struct linked_list *next; // pointer to next node
} LinkedList; // typedef name


/*
 * Main function
 * Will create a linked list and loop until we've reached the user input number to calculate numbers
 * Continually increasing the linked list with our new nodes correctly calculating the fibonacci numbers as we go
 * Then prints the n'th fibonacci number
*/
int main(int argc, char *argv[]) {
    if (argc != 2) { // check if argc is 2
        printf("invalid\n");
        return 0; // stop execution if not
    }
    if (argv[1][0] == '-' || argv[1][0] - '0' < 1) { // if argument is less than 1 or negative
        printf("0\n");
        return 0; // stop execution if not
    }
    
    LinkedList list; // initialize our LL
    long first_number; // initialize and set first number to 1
    long second_number; // initialize and set second number to 1
    LinkedList *item, *old, *head; // create 3 LL nodes
    head = NULL; // set the head to null
    int target_number = atoi(argv[1]); // get our target number

    for (int i = 1; i <= target_number; i++) { // from 1 to user input
        item = (LinkedList*)malloc(sizeof(LinkedList)); // allocate memory for the LL node
        item->next = NULL; // set next to NULL

        if (head == NULL) { // if its the first item (head still null), set head to item
            head = item;
        } else { // else set olds next field to item
            old->next = item;
        }
        // since the first numbers of a fibonacci sequence is abit special
        // we just have a special if case to check if i is less then 3 and set value to 1 if thats the case
        if (i == 1) { // 1st fibo number 0 case
            first_number = 0;
            item->value = first_number;
        } else if (i < 3) { // 2nd fibo number 1 case
            second_number = 1;
            item->value = second_number;
        } else { // else normal fibo sequence
            item->value = first_number + second_number; // value is first + second
            first_number = second_number; // assign second number to first for next iteration
            second_number = item->value; // assign second number is items value for next iteration
        }
        old = item; // set old to the current for the next iteration
    }
    printf("%ld", item->value);

    // freeing LL memory
    LinkedList *current = head; // create and set current node to head
    LinkedList *temp; // create a temp node
    while (current != NULL) { // while current is not null
        temp = current->next; // set temp to current next
        free(current); // free current
        current = temp; // assign temp into current
    }

    return 0; // successful execution
}