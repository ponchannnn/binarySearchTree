#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 64

typedef char String[N];// string as a string

typedef struct node{
    String name;
    String phoneNumber;
    struct node *left;
    struct node *right;
} Node;

Node *mallocNode(String, String);
Node *addData(Node *target_node, Node *add_node){
    if (target_node == NULL) {// if no root, create as a root

        target_node = mallocNode(add_node->name, add_node->phoneNumber);

        if (target_node == NULL) return NULL; // malloc error

        return target_node;
    }


    Node *node = target_node;
    while(1) {
        if (strcmp(add_node->name, node->name) < 0) { // The case new name is lease than root
            if (node->left == NULL) { // if no left node, malloc

                node->left = mallocNode(add_node->name, add_node->phoneNumber); // add new node at left
                break;
            }
            node = node->left; // if has left, switch this to center

        } else if (strcmp(add_node->name, node->name) > 0) { // The case new name is bigger than root
            if (node->right == NULL) {

                node->right = mallocNode(add_node->name, add_node->phoneNumber); // if no right node, malloc
                break;
            }
            node = node->right; // if has right, switch this to center

        } else { // if the new name is same , skip
            printf("%s already exist\n", add_node->name);
            break;
        }
    }
    return target_node;
}

Node *mallocNode(String name, String phoneNumber) {
    Node *add = malloc(sizeof(Node));// malloc
    if (add == NULL) {// check malloc error
        printf("Malloc Error\n");
        return NULL;
    }

    add->left = NULL;// assign, but child -> NULL
    add->right = NULL;
    strcpy(add->name, name); // assign name n phone number
    strcpy(add->phoneNumber, phoneNumber);

    return add;
}

void searchData(Node *target_node, char name[], char number[]) {
    Node *node = target_node; // duplicate
     
    while (node) { // break when node = NULL
        int cmp = strcmp(name, node->name);
        if (cmp < 0) node = node->left; // if lower than target, set to left 
        else if (cmp > 0) node = node->right; // if higher than target, set to right 
        else if (cmp == 0) { // if equal, copy
            strcpy(number, node->phoneNumber);
            return;
        } 
    }
    strcpy(number, "No number");
}

int main() {
    Node *node = NULL;
    int a;
    while(1) {
        printf("If you want to add data, type 0. If none, type other num.\n");
        scanf("%d", &a);
        if (a == 0) {
            String name;
            printf("type name\n");
            scanf("%s", &name);

            String pn;
            printf("type phone number\n");
            scanf("%s", &pn);

            Node new;
            strcpy(new.name, name);
            strcpy(new.phoneNumber, pn);
            new.left = NULL;
            new.right = NULL;

            node = addData(node, &new);
        } else break;
    }

    // searching
    printf("Please type the name of whom you want to search phone number\n");
    String searchName;
    String phoneNumber;
    scanf("%s", searchName);
    searchData(node, searchName, phoneNumber);

    printf("%s's phone number is %s\n", searchName, phoneNumber);
    return 1;
}