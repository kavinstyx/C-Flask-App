#ifndef BST_H
#define BST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50

// Node structure to replace the C++ Node class
typedef struct Node {
    int post_ID, Age, Salary, workingdays, weight, bonus;
    int Marks;
    char Employee_Name[MAX_NAME_LENGTH];
    struct Node* parent;
    struct Node* left;
    struct Node* right;
} Node;

// BST structure to replace the C++ BST class
typedef struct BST {
    Node* root;
    int size;
} BST;

// Function prototypes
BST* create_bst();
void initialize_bst(BST* bst);
Node* create_node(int k, const char* name, int age);
void insert(BST* bst, int k, const char* name, int age);
void print_bst(BST* bst);
void print_values(BST* bst, int k);
void promote_without_retirement(BST* bst, int promoting_ID, int Substitution_ID);
void retire(BST* bst, int decision, int k);
void delete_node(BST* bst, int key);
int salary_calculation(BST* bst, int Get_ID);
int marks(BST* bst, int Get_ID, int addmarks);
int check_marks(BST* bst, int Get_ID);

// Helper function prototypes
void inorder(Node* node);
void preorder(Node* node);
void postorder(Node* node);
void swap(Node* first, Node* second);
void swap_for_promote(Node* first, Node* second);
void heapify(Node* current);
void release_heap(Node* current);
void promote(BST* bst, int promoting_ID, Node* node);

#endif /* BST_H */