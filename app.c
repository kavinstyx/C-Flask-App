// app.c
#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

// Forward declarations
void Choices(int access, int ID);
void insert_employee(int access, int ID);
void search_details(int access, int ID);
void promote_employee(int access, int ID);
void retire_employee(int access, int ID);



int Check_Password_Admin(const char* s, int post_ID); // Defined elsewhere

// Main function
int main() {
    bst = create_bst();

    // Simulate admin login
    printf("Starting Employee Management System\n");
    Choices(1, 1); // access level 1, ID 1

    destroy_bst(bst);
    return 0;
}

// Menu options
void Choices(int access, int ID) {
    int choice;
    do {
        printf("\n=== Main Menu ===\n");
        printf("1. Insert Employee\n");
        printf("2. Search Details\n");
        printf("3. Promote Employee\n");
        printf("4. Retire Employee\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                insert_employee(access, ID);
                break;
            case 2:
                search_details(access, ID);
                break;
            case 3:
                promote_employee(access, ID);
                break;
            case 4:
                retire_employee(access, ID);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 5);
}