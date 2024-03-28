// mymalloc.h

#ifndef MYMALLOC_H
#define MYMALLOC_H

#include <stdbool.h>

struct memory {
    int size;
    bool isFree;
    struct memory* next;
};

extern struct memory* head;
extern char hard[25000];
extern const int heap_size;

void* MyMalloc(int size);
void MyFree(void* ptr);

#endif
