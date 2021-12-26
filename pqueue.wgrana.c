//
// Created by Will Grana on 9/28/20.
//
#include "pqueue.wgrana.h"
#include <stdlib.h>
#include <stdio.h>


int enqueue(PQueueNode **pqueue, int priority, void *data) {
    PQueueNode *n;
    n = (struct PQueueNode*)malloc(sizeof(PQueueNode));
    n->priority = priority;
    n->data = data;
    if (*pqueue == NULL) {
        n->next = NULL;
        (*pqueue)=n;
    }
    else {
        PQueueNode* n1 = *pqueue;
        int counter = 0;
        while ((n1)->next!=NULL && n->priority >= (n1)->priority) {
            n1 = n1->next;
            counter++;
        }
        if (n1->priority < n->priority) {
            n1->next = n;
            n->next = NULL;
        }
        else if (counter==0) {
            n->next=*pqueue;
            *pqueue = n;
        }
        else {
            n->next = n1;
            n1 = *pqueue;
            for (int i = 0; i < counter - 1; i++) {
                n1 = n1->next;
            }
            n1->next = n;
        }
    }

}

void *dequeue(PQueueNode **pqueue) {
    if (*pqueue != NULL) {
        PQueueNode* n = *pqueue;
        *pqueue = (*pqueue)->next;
        return n->data;
    }
    else {
        return NULL;
    }
}

void *peek(PQueueNode *pqueue) {
    return pqueue->data;
}

void printQueue(PQueueNode *pqueue, void (printFunction)(void*)) {
    PQueueNode* head = pqueue;
    while (head != NULL) {
        printf("priority = %d ", head->priority);
        printf("data = ");
        printFunction(head->data);
        head = head->next;
    }

}

int getMinPriority(PQueueNode *pqueue) {
    if (pqueue != NULL) {
        return pqueue->priority;
    }
    else {
        return -1;
    }
}

int queueLength(PQueueNode *pqueue) {
    PQueueNode* head = pqueue;
    int counter = 0;
    while (pqueue != NULL) {
        counter++;
        pqueue = pqueue->next;
    }
    pqueue = head;
    return counter;
}

void printSong(void *data) {
    printf("\"%s\"", ((Song*)data)->title);
    printf(" (%s)\n", ((Song*)data)->artist);
}