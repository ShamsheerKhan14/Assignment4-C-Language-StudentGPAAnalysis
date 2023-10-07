
// ***** DO NOT CHANGE OR ADD ANY CODE IN THIS FILE *****
#include <stdbool.h>
#define NAME_STR_LEN  26

// Singly linked list node structure representing one student
typedef struct node {
    char lastName[NAME_STR_LEN];
    char firstName[NAME_STR_LEN];
    long int ID;
    double GPA;
    struct node* next;       // Next student in list towards the tail
} Node;

// Singly linked list abstract data type (has both head & tail pointers)
typedef struct {
    Node* head;         // Head (front) of the linked list
    Node* tail;         // Tail (back) of the linked list
} List;

// List operations
List* initList(void);
bool isEmpty(List* L);
Node* createNode(char lastName[], char firstName[], long int ID, double GPA);
void appendNode(List* L, Node* st);
Node* removeNode(List* L);


