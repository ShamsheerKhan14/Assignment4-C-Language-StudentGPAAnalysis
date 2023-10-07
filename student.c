#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "LinkedList3.h"

/* PROG20799 Project
   Student Name: Shamsheer Khan, Gurjot Singh
   Student ID  : 991661386     , 991629832
 */

// Function prototype for readFile
int readFile(const char fileName[]);
void inOrderTraversal(Node* root);

// Function to perform Bubble Sort and count comparisons
long long int bubbleSort(double arr[], int n) {
    long long int comparisons = 0;
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (arr[j] < arr[j + 1]) {
                double temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        // If no two elements were swapped in the inner loop, the array is already sorted
        if (!swapped) {
            break;
        }
    }
    return comparisons;
}

// Function to compare GPA values for qsort
int compareGPA(const void* a, const void* b) {
    double gpaA = *((double*) a);
    double gpaB = *((double*) b);

    if (gpaA > gpaB) {
        return -1;
    } else if (gpaA < gpaB) {
        return 1;
    }
    return 0;
}


// Structure representing a node in a binary search tree (BST) with 'GPA' value and left and right child pointers.
typedef struct bstNode {
    double GPA;
    struct bstNode* left;
    struct bstNode* right;
} BSTNode;

// Function to create a balanced binary search tree from a sorted array
BSTNode* rootInsert(BSTNode* root, double GPA) {
    if (root == NULL) {
        root = (BSTNode*) malloc(sizeof (BSTNode));
        root->GPA = GPA;
        root->left = NULL;
        root->right = NULL;
    } else if (GPA >= root->GPA) {
        root->right = rootInsert(root->right, GPA);
    } else {
        root->left = rootInsert(root->left, GPA);
    }
    return root;
}

List* list = NULL; // Initialize the linked list pointer

// Function to read file and return the number of lines read
int readFile(const char fileName[]) {
    // Initialize the linked list
    list = initList();

    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", fileName);
        return -1;
    }

    char buffer[256];
    int lines = 0;
    while (fgets(buffer, sizeof (buffer), file)) {
        // Process each line if needed
        // For now, we just count the lines
        char lastName[100], firstName[100];
        int ID;
        double GPA;

        // Use sscanf to extract the data from the line
        int result = sscanf(buffer, "%[^,],%[^,],%d,%lf", lastName, firstName, &ID, &GPA);
        if (result == 4) {
            // Successfully read all fields
            // Now you can use the provided appendNode function to add the student to the linked list
            Node* newNode = createNode(lastName, firstName, ID, GPA);
            appendNode(list, newNode);
            lines++; // Increment the lines count
        }
    }

    fclose(file);
    return lines;
}

// Function to perform an in-order traversal of a binary search tree (BST) rooted at 'root'
void bstInOrderTraversal(BSTNode * root) {
    if (root == NULL) {
        return;
    }

    bstInOrderTraversal(root->left);
    printf("%.2lf ", root->GPA);
    bstInOrderTraversal(root->right);
}

int main(int argc, char** argv) {
    int lines = readFile("studentlist.txt");
    //int lines = readFile("studentlisthalf.txt");

    if (lines <= 0) {
        printf("Quitting due to error or empty file.\n");
        return 1;
    }

    printf("\n%d lines read from the file.\n", lines);

    // Create an array to hold the GPA values
    double gpaArray[lines];
    int i = 0;

    // Traverse the linked list and populate the GPA array
    Node* current = list->head;
    while (current != NULL) {
        gpaArray[i] = current->GPA;
        current = current->next;
        i++;
    }

    // Perform Bubble Sort on the GPA array and get the number of comparisons
    long long int bubbleSortComparisons = bubbleSort(gpaArray, lines);
    // Print the first 50 sorted GPA values
    printf("\nTop 50 GPA values (descending order) after Bubble Sort:\n");
    for (int j = 0; j < 50 && j < lines; j++) {
        printf("%.2lf\n", gpaArray[j]);
    }

    // Print the number of comparisons for Bubble Sort
    printf("\nNumber of comparisons for Bubble Sort: %lld\n", bubbleSortComparisons);

    // Sorting using qsort
    qsort(gpaArray, lines, sizeof (double), compareGPA);

    // Print the first 50 sorted GPA values using qsort
    printf("\nTop 50 GPA values (descending order) after qsort:\n");
    for (int j = 0; j < 50 && j < lines; j++) {
        printf("%.2lf\n", gpaArray[j]);
    }

    // Print the number of comparisons for qsort
    printf("\nNumber of comparisons for qsort: %d\n", compareGPA);
    // Creating the binary search tree from the sorted array
    BSTNode* root = NULL;
    for (int i = 0; i < lines; i++) {
        root = rootInsert(root, gpaArray[i]);
    }

    // Print the entire resulting tree using in-order traversal
    printf("\nBST in-order traversal:\n");
    bstInOrderTraversal(root);

    // Print the value at the root of the tree, it should be in the middle of the list
    printf("\nValue at the root of the BST: %.2lf\n", root->GPA);

    return 0;
}
