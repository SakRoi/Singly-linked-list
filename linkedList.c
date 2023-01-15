#include <stdio.h>
#include <stdlib.h>

//the node struct
typedef struct{
    void *next;
    int data;
} node;

//when starting the program, the head or the first node is always NULL
node *head = NULL;

//add node
node *addNode(int dataArgument)
{
    //allocating memory for the new node
    node *new = malloc(sizeof(node));

    //if something goes bad
    if (new == NULL){
        return NULL;
    }

    //if there isn't first node
    if (head == NULL){
        new->data = dataArgument;
        head = new;
        new->next = NULL;
    }
    //if there is a first node, move old first node to the next node and make the new node the first node
    else {
        new->data = dataArgument;
        new->next = head;
        head = new;
    }

    return new;
}

//remove node
int removeNode(int positionArgument){
    //make both current and prev node point to the head node
    node *current = head;
    node *prev = head;
    int currentPosition = 0;
    //while the current doesn't point to null
    while (current != NULL){
        if (currentPosition == positionArgument){
            //checks if wanted position is the head
            if (positionArgument == 0){
            head = current->next;
            } else {
                prev->next = current->next;
            }
            //freeing memory from the removed node
            free(current);
            current = NULL;
            return 1;
        }
    currentPosition++;
    prev = current;
    current = current->next;
    }
    return 0;
}

//insert node
node *insertNode(int dataArgument, int positionArgument){
    node *current = head;

    while (current->next != NULL && positionArgument != 0){
        positionArgument--;
        current = current->next;
    }

    if (positionArgument != 0){
        printf("Requested position was too far into the list, give a smaller position argument");
        return NULL;
    }
    node *new = malloc(sizeof(node));
    if (new == NULL){
        return NULL;
    }

    new->data = dataArgument;
    new->next = current->next;
    current->next = new;

    return new;
}

//print nodes

void printList(){
    node *current = head;
    while (current != NULL){
        printf("%d->", current->data);
        current = current->next;
    }
    printf("\n");
    return;
}


void printMenu(){
    printf("You have the following options:\n");
    printf("1: Add a Node:\n");
    printf("2: Remove a Node:\n");
    printf("3: Insert a Node:\n");
    printf("4: Print the Nodes:\n");
    printf("5: quit:\n");
}

void clearNodes(){
    node *current = head;
    node *prev = head;
    while (current != NULL){
        if (current->next == NULL){
            free(current);
            current = NULL;
        } else {
            prev = current;
            current = current->next;
            free(prev);
            prev == NULL;
        }
    }
}

int main(int argc, char **argv)
{
    int option = -1;
    int dataArgument = 0;
    int positionArgument = 0;
    while (option != 5)
    {
        printMenu();
        int num_received = scanf("%d", &option);
        if (num_received == 1 && option > 0 && option <= 5)
        {
            switch(option)
            {
                case 1:
                    // add operation
                    printf("What data should I insert?:\n");
                    scanf("%d", &dataArgument);
                    node *new = addNode(dataArgument);
                    break;
                case 2:
                    // remove operation
                    printf("What position should I remove? Note that first element = 0 and so forth:\n");
                    scanf("%d", &positionArgument);
                    int success = removeNode(positionArgument);
                    if (!success)
                        printf("Element not found\n");

                    break;
                case 3:
                    // insert operation
                    // remove operation
                    printf("What data should I insert?:\n");
                    scanf("%d", &dataArgument);
                    printf("What position?:\n");
                    scanf("%d", &positionArgument);
                    new = insertNode(dataArgument, positionArgument);
                    if (new == NULL)
                        printf("Failed to insert into list\n");
                    break;
                case 4:
                    // print the list
                    printList();
                    break;
                case 5:
                clearNodes();
                    break;
            }
        }
    }
    

    return 0;
}