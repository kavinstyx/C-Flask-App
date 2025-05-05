#include "bst.h"

// Create a new BST
BST* create_bst() {
    BST* bst = (BST*)malloc(sizeof(BST));
    if (bst != NULL) {
        initialize_bst(bst);
    }
    return bst;
}

// Initialize BST
void initialize_bst(BST* bst) {
    bst->root = NULL;
    bst->size = 0;
}
void free_bst(Node* node) {
    if (node != NULL) {
        free_bst(node->left);
        free_bst(node->right);
        free(node);
    }
}

void destroy_bst(BST* bst) {
    if (bst != NULL) {
        free_bst(bst->root);
        free(bst);
    }
}
// In-order traversal to print all employees
void in_order_traversal(Node* node) {
    if (node != NULL) {
        in_order_traversal(node->left);
        printf("Post ID: %d, Name: %s, Age: %d\n", node->id, node->name, node->age);
        in_order_traversal(node->right);
    }
}

// Create a new node
Node* create_node(int k, const char* name, int age) {
    Node* temp = (Node*)malloc(sizeof(Node));
    if (temp != NULL) {
        temp->post_ID = k;
        strncpy(temp->Employee_Name, name, MAX_NAME_LENGTH - 1);
        temp->Employee_Name[MAX_NAME_LENGTH - 1] = '\0'; // Ensure null termination
        temp->Age = age;
        temp->Salary = 5000;
        temp->Marks = 30;
        temp->workingdays = 10;
        temp->weight = 0;
        temp->bonus = 0;
        temp->parent = NULL;
        temp->left = NULL;
        temp->right = NULL;
    }
    return temp;
}

// Insert a new node into the BST
void insert(BST* bst, int k, const char* name, int age) {
    Node* temp = create_node(k, name, age);
    if (temp == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    Node* current = bst->root;
    Node* prev = NULL;

    if (bst->root == NULL) {
        bst->root = temp;
    } else {
        while (current != NULL) {
            prev = current;
            if (k > current->post_ID) {
                current = current->right;
            } else if (k < current->post_ID) {
                current = current->left;
            } else {
                printf("Duplicate values are not allowed\n");
                free(temp);
                return;
            }
        }

        if (k > prev->post_ID) {
            prev->right = temp;
            temp->parent = prev;
        } else if (k < prev->post_ID) {
            prev->left = temp;
            temp->parent = prev;
        }
    }
    bst->size++;
}

// Print functions for traversal
void inorder(Node* node) {
    if (node != NULL) {
        inorder(node->left);
        printf(" | %d", node->post_ID);
        inorder(node->right);
    }
}

void preorder(Node* node) {
    if (node != NULL) {
        printf(" | %d", node->post_ID);
        preorder(node->left);
        preorder(node->right);
    }
}

void postorder(Node* node) {
    if (node != NULL) {
        postorder(node->left);
        postorder(node->right);
        printf(" | %d", node->post_ID);
    }
}

// Print the BST
void print_bst(BST* bst) {
    printf("\nIn-order Data : ");
    inorder(bst->root);
    printf("\nPre-order Data : ");
    preorder(bst->root);
    printf("\nPost-order Data : \n");
    postorder(bst->root);
}

// Swap function for heap operations
void swap(Node* first, Node* second) {
    int temp_post_ID = first->post_ID;
    char temp_name[MAX_NAME_LENGTH];
    strncpy(temp_name, first->Employee_Name, MAX_NAME_LENGTH);
    int temp_age = first->Age;
    int temp_salary = first->Salary;
    int temp_marks = first->Marks;
    int temp_workingdays = first->workingdays;
    int temp_weight = first->weight;
    int temp_bonus = first->bonus;

    first->post_ID = second->post_ID;
    strncpy(first->Employee_Name, second->Employee_Name, MAX_NAME_LENGTH);
    first->Age = second->Age;
    first->Salary = second->Salary;
    first->Marks = second->Marks;
    first->workingdays = second->workingdays;
    first->weight = second->weight;
    first->bonus = second->bonus;

    second->post_ID = temp_post_ID;
    strncpy(second->Employee_Name, temp_name, MAX_NAME_LENGTH);
    second->Age = temp_age;
    second->Salary = temp_salary;
    second->Marks = temp_marks;
    second->workingdays = temp_workingdays;
    second->weight = temp_weight;
    second->bonus = temp_bonus;
}

// Special swap for promote functionality
void swap_for_promote(Node* first, Node* second) {
    char temp_name[MAX_NAME_LENGTH];
    strncpy(temp_name, first->Employee_Name, MAX_NAME_LENGTH);
    int temp_age = first->Age;
    int temp_marks = first->Marks;
    int temp_workingdays = first->workingdays;

    strncpy(first->Employee_Name, second->Employee_Name, MAX_NAME_LENGTH);
    first->Age = second->Age;
    first->Marks = second->Marks;
    first->workingdays = second->workingdays;

    strncpy(second->Employee_Name, temp_name, MAX_NAME_LENGTH);
    second->Age = temp_age;
    second->Marks = temp_marks;
    second->workingdays = temp_workingdays;
}

// Heapify function (max-heap)
void heapify(Node* current) {
    if (current == NULL)
        return;
    heapify(current->left);
    heapify(current->right);

    if (current->left != NULL && current->left->post_ID > current->post_ID) {
        swap(current, current->left);
        heapify(current);
    }

    if (current->right != NULL && current->right->post_ID > current->post_ID) {
        swap(current, current->right);
        heapify(current);
    }
}

// Release heap (convert back to BST)
void release_heap(Node* current) {
    if (current == NULL)
        return;
    release_heap(current->left);
    release_heap(current->right);

    if (current->left != NULL && current->left->post_ID > current->post_ID) {
        swap(current, current->left);
        release_heap(current);
    }

    if (current->right != NULL && current->right->post_ID < current->post_ID) {
        swap(current, current->right);
        release_heap(current);
    }
}

// Print values for a specific post ID
void print_values(BST* bst, int k) {
    release_heap(bst->root);

    if (bst->root == NULL) {
        printf("List is empty\n");
    } else {
        Node* current = bst->root;
        while (current != NULL) {
            if (current->post_ID == k) {
                printf("\n\tPost ID                   : %d\n", current->post_ID);
                printf("\tName                      : %s\n", current->Employee_Name);
                printf("\tAge                       : %d\n", current->Age);
                printf("\tSalary                    : %d\n", current->Salary);
                printf("\tNo. of Working Days       : %d\n", current->workingdays);
                printf("\tMarks within the position : %d\n", current->Marks);
                heapify(bst->root);
                return;
            } else if (k < current->post_ID) {
                current = current->left;
            } else if (k > current->post_ID) {
                current = current->right;
            }
        }
        printf("Post ID not found\n");
    }
    heapify(bst->root);
}

// Function to promote employee
void promote(BST* bst, int promoting_ID, Node* node) {
    release_heap(bst->root);

    int Manager_marks = 50;
    int Director_marks = 75;

    if (bst->root == NULL) {
        printf("List is empty\n");
    } else {
        Node* current = bst->root;
        while (current != NULL) {
            if (current->post_ID == promoting_ID && node != NULL) {
                if (current->Marks >= Director_marks) {
                    swap_for_promote(current, node);
                    delete_node(bst, current->post_ID);
                    break;
                } else if (current->Marks >= Manager_marks) {
                    swap_for_promote(current, node);
                    delete_node(bst, current->post_ID);
                    break;
                } else {
                    printf("\tMarks insufficient for promotion");
                    break;
                }
            } else if (promoting_ID < current->post_ID) {
                current = current->left;
            } else if (promoting_ID > current->post_ID) {
                current = current->right;
            }
        }
    }
    heapify(bst->root);
}

// Function to promote without retirement
void promote_without_retirement(BST* bst, int promoting_ID, int Substitution_ID) {
    release_heap(bst->root);
    int Manager_marks = 50;
    int Director_marks = 75;

    if (bst->root == NULL) {
        printf("List is empty\n");
    } else {
        Node* current = bst->root;
        while (current != NULL) {
            if (current->post_ID == promoting_ID) {
                if (current->Marks >= Director_marks) {
                    current->post_ID = Substitution_ID;
                } else if (current->Marks >= Manager_marks) {
                    current->post_ID = Substitution_ID;
                } else {
                    printf("\tMarks insufficient for promotion");
                }
                break;
            } else if (promoting_ID < current->post_ID) {
                current = current->left;
            } else if (promoting_ID > current->post_ID) {
                current = current->right;
            }
        }
    }
    heapify(bst->root);
}

// Function to retire an employee
void retire(BST* bst, int decision, int k) {
    release_heap(bst->root);

    if (bst->root == NULL) {
        printf("\tList is empty\n");
    } else {
        Node* current = bst->root;
        while (current != NULL) {
            if (current->post_ID == k) {
                if (decision == 1) {
                    printf("\tInput the ID for promotion : ");
                    int P_ID;
                    scanf("%d", &P_ID);
                    promote(bst, P_ID, current);
                    break;
                } else {
                    delete_node(bst, current->post_ID);
                    break;
                }
            } else if (k < current->post_ID) {
                current = current->left;
            } else if (k > current->post_ID) {
                current = current->right;
            }
        }
    }
    heapify(bst->root);
}

// Function to delete a node
void delete_node(BST* bst, int key) {
    release_heap(bst->root);

    if (bst->root == NULL) {
        printf("\tList is empty\n");
    } else {
        Node* current = bst->root;
        while (current != NULL && current->post_ID != key) {
            if (key < current->post_ID) {
                current = current->left;
            } else if (key > current->post_ID) {
                current = current->right;
            }
        }

        if (current == NULL) {
            printf("\tSearched ID does not exist\n");
        } else if (current->left == NULL && current->right == NULL) { // leaf node
            if (current == bst->root) {
                bst->root = NULL;
            } else if (current->post_ID < current->parent->post_ID) {
                current->parent->left = NULL;
            } else {
                current->parent->right = NULL;
            }
            free(current);
            bst->size--;
        } else if (current->left == NULL) { // has right child only
            if (current == bst->root) {
                bst->root = current->right;
                bst->root->parent = NULL;
            } else if (current->post_ID < current->parent->post_ID) {
                current->parent->left = current->right;
                current->right->parent = current->parent;
            } else {
                current->parent->right = current->right;
                current->right->parent = current->parent;
            }
            free(current);
            bst->size--;
        } else if (current->right == NULL) { // has left child only
            if (current == bst->root) {
                bst->root = current->left;
                bst->root->parent = NULL;
            } else if (current->post_ID < current->parent->post_ID) {
                current->parent->left = current->left;
                current->left->parent = current->parent;
            } else {
                current->parent->right = current->left;
                current->left->parent = current->parent;
            }
            free(current);
            bst->size--;
        } else { // has two children
            // Find max in left subtree
            Node* max = current->left;
            while (max->right != NULL) {
                max = max->right;
            }

            current->post_ID = max->post_ID;
            strncpy(current->Employee_Name, max->Employee_Name, MAX_NAME_LENGTH);
            current->Age = max->Age;
            current->Salary = max->Salary;
            current->Marks = max->Marks;
            current->workingdays = max->workingdays;
            current->weight = max->weight;
            current->bonus = max->bonus;

            if (max == current->left) {
                current->left = max->left;
                if (max->left != NULL) {
                    max->left->parent = current;
                }
            } else {
                max->parent->right = max->left;
                if (max->left != NULL) {
                    max->left->parent = max->parent;
                }
            }
            free(max);
            bst->size--;
        }
    }
    heapify(bst->root);
}

// Calculate salary
int salary_calculation(BST* bst, int Get_ID) {
    release_heap(bst->root);
    int result = 0;

    if (bst->root == NULL) {
        printf("List is empty\n");
    } else {
        Node* current = bst->root;
        while (current != NULL) {
            if (current->post_ID == Get_ID) {
                int temp_Salary = current->Salary;
                int basic = 0;

                if (current->post_ID >= 17) {
                    basic = 100000;
                    current->weight = 10;
                } else if (current->post_ID >= 12) {
                    basic = 80000;
                    current->weight = 8;
                } else if (current->post_ID >= 9) {
                    basic = 65000;
                    current->weight = 7;
                } else if (current->post_ID >= 6) {
                    basic = 40000;
                    current->weight = 6;
                } else {
                    basic = 20000;
                    current->weight = 3;
                }

                if (current->Marks >= 100) {
                    current->bonus = 30000;
                } else if (current->Marks >= 75) {
                    current->bonus = 22500;
                } else if (current->Marks >= 50) {
                    current->bonus = 15000;
                } else if (current->Marks >= 35) {
                    current->bonus = 5000;
                } else {
                    current->bonus = 0;
                }

                temp_Salary = basic + 100 * current->workingdays * current->weight + current->bonus;
                current->Salary = temp_Salary;
                result = temp_Salary;
                break;
            } else if (Get_ID < current->post_ID) {
                current = current->left;
            } else if (Get_ID > current->post_ID) {
                current = current->right;
            }
        }
        if (result == 0) {
            printf("Post ID not found\n");
        }
    }
    heapify(bst->root);
    return result;
}

// Add or check marks
int marks(BST* bst, int Get_ID, int addmarks) {
    release_heap(bst->root);
    int temp_marks = 0;

    if (bst->root == NULL) {
        printf("\tList is empty\n");
    } else {
        Node* current = bst->root;
        while (current != NULL) {
            if (current->post_ID == Get_ID) {
                temp_marks = current->Marks;
                temp_marks += addmarks;
                current->Marks = temp_marks;
                
                if (addmarks > 0) {  // Only display these messages when actually adding marks
                    if (temp_marks >= 100) {
                        printf("\n\tRewarded...\n");
                    } else {
                        printf("\tWarning...\n");
                    }
                }
                
                break;
            } else if (Get_ID < current->post_ID) {
                current = current->left;
            } else if (Get_ID > current->post_ID) {
                current = current->right;
            }
        }
        if (temp_marks == 0) {
            printf("\tPost ID not found\n");
        }
    }
    heapify(bst->root);
    return temp_marks;
}

// Check marks (calls marks with addmarks=0)
int check_marks(BST* bst, int Get_ID) {
    return marks(bst, Get_ID, 0);
}

