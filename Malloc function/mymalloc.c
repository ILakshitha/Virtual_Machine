

#include <stdio.h>
#include "mymalloc.h"

struct memory* head = NULL;
char hard[25000];
const int heap_size = sizeof(hard);

void *MyMalloc (int size)
{
    if (head == NULL)
    {
        head = (struct memory*) &hard[0];
        head->size = heap_size - sizeof(struct memory);
        head->isFree = true;
        head->next = NULL;
    } 

    struct memory* current = head;
    struct memory* previous = NULL;
    
    while (current != NULL && !(current->isFree && current->size >= size)) 
    {
        previous = current;
        current = current->next;
    } 


    if(current !=NULL) 
    {
        current->isFree = false; 

        if (current->size > size + sizeof(struct memory))
        {
            struct memory *new = (struct memory *) ((char *)current + size + sizeof(struct memory));
            new->size = current->size - size - sizeof(struct memory);
            new->isFree = true;
            current->size = size;
            new->next = current->next;
            current->next = new;
        }
        return (void *)current + sizeof(struct memory);

    }
    return NULL;
}


void MyFree(void* ptr) {
    if (ptr == NULL) {
        return;
    }

    struct memory* current = head;
    struct memory* previous = NULL;

    while (current != NULL && (char*)current + sizeof(struct memory) != ptr) {
        previous = current;
        current = current->next;
    }

    if (current != NULL) {
        current->isFree = true;

        // Merge blocks
        if (previous != NULL && previous->isFree) {
            previous->size += current->size + sizeof(struct memory);
            previous->next = current->next;
        }

        if (current->next != NULL && current->next->isFree) {
            current->size += current->next->size + sizeof(struct memory);
            current->next = current->next->next;
        }
    } else {
        printf("Invalid or already freed struct memory block\n");
    }
}