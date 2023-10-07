#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "LinkedList3.h"

// ***** DO NOT CHANGE OR ADD ANY CODE IN THIS FILE *****

// Initialize a new linked list ADT.
// The caller is responsible for eventually freeing the returned pointer.
List* initList(void) {
    List* lp = (List*)malloc(sizeof(List));
    lp->head = NULL;
    lp->tail = NULL;
    return lp;
}

// Check if the list is empty
bool isEmpty(List* L) {
    return (L->head == NULL && L->tail == NULL);
}

// Create a linked list node (student), including memory allocation.
Node* createNode(char lastName[], char firstName[], long int ID, double GPA) {
	Node* st = malloc(sizeof(Node));
	strcpy(st->lastName, lastName);
	strcpy(st->firstName, firstName);
	st->ID = ID;
	st->GPA = GPA;
	st->next = NULL;    // Next pointer null for now
	return st;
}

// Add the node (student) 'st' on the tail of linked list 'L'.
void appendNode(List* L, Node* st) {
	if (isEmpty(L)) {
		L->head = st;    // One item in the list, both head and tail point at it
		L->tail = st;
	}
	else {
		L->tail->next = st;   // Add item at the tail
		L->tail = st;
	}
} 

// Remove item at the head of the list 'L'.
// Returns the node (student) pointer, or NULL if the list is empty.
// Important: The caller should free the removed node if it will no longer be used.
Node* removeNode(List* L) {
    if (isEmpty(L)) {
        return NULL;    // Special value indicates error
    }
	else {
        Node* result = L->head;  // Get item from the head
        L->head = L->head->next;       // Unlink the head node
        if (L->head == NULL) {         // If the list became empty then show there is no tail
            L->tail = NULL;
        }
            
        return result;     // Return the node pointer
    }
} 

