#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



// Function prototypes
int main();
void Choices(int access, int ID);
int Check_Password_Admin(const char* s, int post_ID);
void insert_employee(int access, int ID);
void search_details(int access, int ID);
void promote_employee(int access, int ID);
void retire_employee(int access, int ID);
void print_all(int access, int ID);
void salary_calculation_ui(int access, int ID);
void add_marks(int access, int ID);
void search_marks(int access, int ID);

// Global BST
BST* bst;

// Password and Access Level Checker
int Check_Password_Admin(const char* s, int post_ID) {
    const char* pw1 = "Chairman";    // Chairman
    const char* pw2 = "Director1";   // Director1
    const char* pw3 = "Director2";   // Director2
    const char* pw4 = "Manager1";    // Manager1
    const char* pw5 = "Manager2";    // Manager2
    const char* pw8 = "Employee";    // Employee

    int ID1 = 1;
    int ID2 = 2;
    int ID3 = 3;
    int ID4 = 4;
    int ID5 = 5;
    int ID8 = 8;

    if (strcmp(s, pw1) == 0 && post_ID == ID1)
        return 1;
    else if (strcmp(s, pw2) == 0 && post_ID == ID2)
        return 2;
    else if (strcmp(s, pw3) == 0 && post_ID == ID3)
        return 2;
    else if (strcmp(s, pw4) == 0 && post_ID == ID4)
        return 3;
    else if (strcmp(s, pw5) == 0 && post_ID == ID5)
        return 3;
    else if (strcmp(s, pw8) == 0 && post_ID == ID8)
        return 4;
    else {
        printf("Password or Post ID is incorrect. Please re-enter the Password and the Post ID\n\n");
        return 0;
    }
}

// Main Menu Options
void Choices(int access, int ID) {
    printf("*** Main Menu ***\n\n");

    printf("\t1. Insert Employee\n");
    printf("\t2. Search Employee Details\n");
    printf("\t3. Promote Employee\n");
    printf("\t4. Retire Employee\n");
    printf("\t5. Print All Employees\n");
    printf("\t6. Exit\n\n");

    printf("\tEnter your choice: ");
    int choice;
    scanf("%d", &choice);
    printf("\n");

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
            print_all(access, ID);
            break;
        case 6:
            printf("Exiting...\n");
            exit(0);
        default:
            printf("Invalid choice.\n");
            Choices(access, ID);
    }
}

// Entry point of program
int main() {
    // Initialize BST
    bst = create_bst();

    // Dummy login simulation
    printf("Enter password: ");
    char password[50];
    scanf("%s", password);

    printf("Enter Post ID: ");
    int post_id;
    scanf("%d", &post_id);

    int access_level = Check_Password_Admin(password, post_id);

    if (access_level > 0) {
        Choices(access_level, post_id);
    } else {
        printf("Login failed.\n");
    }

    return 0;
}

// Function to add employee data to the system
void insert_employee(int access, int ID) {
    printf("*** Adding employees data to the system ***\n\n");

    if (access) {
        printf("\tNo. of members to be added : ");
        int p;
        scanf("%d", &p);
        
        for (int i = 0; i < p; i++) {
            printf("\n\t ** Entering employee %d Data **\n\n", i + 1);
            
            printf("\tEnter preferred Post ID  : ");
            int emp_ID;
            scanf("%d", &emp_ID);
            
            printf("\tEnter employee name : ");
            char name[MAX_NAME_LENGTH];
            scanf("%s", name);
            
            printf("\tEnter employee Age  : ");
            int age;
            scanf("%d", &age);

            // Call insert function
            insert(bst, emp_ID, name, age);
            printf("\n");
        }
    } else {
        printf("\tYou cannot insert employee data\n");
    }

    int input;
    printf("\n\t 1 . Back to Main Menu\n");
    printf("\t 2 . Re-Login\n");
    printf("\t 3 . Exit\n\n");
    printf("\t Enter your choice : ");
    scanf("%d", &input);
    printf("\n");

    if (input == 1)
        Choices(access, ID);
    else if (input == 2)
        main();
    else
        printf("\nThank you, Have a Good day!!!\n");
}

// Function to search employee details
void search_details(int access, int ID) {
    printf("*** Searching Employee Details ***\n\n");

    if (access != 0) {
        int k;
        printf("\tInsert the Post ID to be searched : ");
        scanf("%d", &k);
        printf("\n");

        if (access == 1 && k >= 1)
            print_values(bst, k);
        else if (access == 2 && k == 1)
            printf("\tYou are not allowed to access this data\n");
        else if (access == 2 && k >= 2)
            print_values(bst, k);
        else if ((access == 3 && k == 1) || (access == 3 && k == 2))
            printf("\tYou are not allowed to access this data\n");
        else if (access == 3 && k == 3)
            print_values(bst, k);
    }

    if (access == 0)
        print_values(bst, ID);

    int input;
    printf("\n\t 1 . Back to Main Menu\n");
    printf("\t 2 . Re-Login\n");
    printf("\t 3 . Exit\n\n");
    printf("Enter your choice : ");
    scanf("%d", &input);
    printf("\n");

    if (input == 1)
        Choices(access, ID);
    else if (input == 2)
        main();
    else
        printf("\nThank you Have a Good day!!!\n");
}

// Function to promote an employee
void promote_employee(int access, int ID) {
    printf("***Promoting an employee\n\n");

    int k; // Post Id that needs to be promoted
    printf("\tInsert the Post ID to be promoted    : ");
    scanf("%d", &k);

    int t; // Target post ID to promote
    printf("\tInsert the target Post ID to promote : ");
    scanf("%d", &t);

    if (access == 1 && k > 1)
        promote_without_retirement(bst, k, t);
    else if (access == 2 && k == 1)
        printf("\tYou are not allowed to promote\n");
    else if (access == 2 && k > 2)
        promote_without_retirement(bst, k, t);
    else if ((access == 3 && k == 1) || (access == 3 && k == 2))
        printf("\tYou are not allowed to promote\n");
    else if (access == 3 && k == 0)
        promote_without_retirement(bst, k, t);
    else if ((access == 0 && k == 1) || (access == 0 && k == 2) || (access == 0 && k == 3))
        printf("\tYou are not allowed to promote\n");
    else
        printf("\tYou are not allowed to use this option\n");

    int input;
    printf("\n\t1 . Back to Main Menu\n");
    printf("\t2 . Re-Login\n");
    printf("\t3 . Exit\n\n");
    printf("\tEnter your choice : ");
    scanf("%d", &input);
    printf("\n");

    if (input == 1)
        Choices(access, ID);
    else if (input == 2)
        main();
    else
        printf("\n\tThank you Have a Good day!!!\n");
}

// Function to retire an employee
void retire_employee(int access, int ID) {
    printf("\t*** To retire an employee ***\n\n");

    int k; // The post that needs to retire
    printf("\tInsert the Post ID to be retired : ");
    scanf("%d", &k);

    int selection;
    // When need to promote another employee for the position
    printf("\n\t1. Want to promote another employee for this position\n");
    // Only to retire the employee
    printf("\t2. Only for retirement of this employee\n\n");
    printf("\tEnter your option : ");
    scanf("%d", &selection);
    printf("\n");

    if (access == 1 && k > 1)
        retire(bst, selection, k);
    else if (access == 2 && k == 1)
        printf("\tYou are not allowed to use this option\n");
    else if (access == 2 && k > 2)
        retire(bst, selection, k);
    else if ((access == 3 && k == 1) || (access == 3 && k == 2))
        printf("\tYou are not allowed to use this option\n");
    else if (access == 3 && k == 0)
        retire(bst, selection, k);
    else if ((access == 0 && k == 1) || (access == 0 && k == 2) || (access == 0 && k == 3))
        printf("\tYou are not allowed to use this option\n");
    else
        printf("\tYou are not allowed to use this option\n");

    int input;
    printf("\n\t1 . Back to Main Menu\n");
    printf("\t2 . Re-Login\n");
    printf("\t3 . Exit\n\n");
    printf("\tEnter your choice : ");
    scanf("%d", &input);
    printf("\n");

    if (input == 1)
        Choices(access, ID);
    else if (input == 2)
        main();
    else
        printf("\n\tThank you Have a Good day!!!\n");
}

// Placeholder for print_all function
void print_all(int access, int ID) {
    printf("*** Printing all employees ***\n\n");
    in_order_traversal(bst->root);  // Make sure this is defined in bst.c

    int input;
    printf("\n\t1 . Back to Main Menu\n");
    printf("\t2 . Re-Login\n");
    printf("\t3 . Exit\n\n");
    printf("\tEnter your choice : ");
    scanf("%d", &input);
    printf("\n");

    if (input == 1)
        Choices(access, ID);
    else if (input == 2)
        main();
    else
        printf("\nThank you, Have a Good day!!!\n");
}