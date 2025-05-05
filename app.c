#include "bst.h"
#include <stdio.h>

// Declare external functions
void insert_employee(int access, int ID);
void search_details(int access, int ID);
void promote_employee(int access, int ID);
void retire_employee(int access, int ID);
void Choices(int access, int ID);

// Dummy login for demo
int Check_Password_Admin(const char* s, int post_ID);

int main() {
    BST* bst = create_bst();

    // Dummy login logic for testing
    printf("Starting employee management system...\n");
    Choices(1, 1); // Simulate admin login

    destroy_bst(bst);
    return 0;
}