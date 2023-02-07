#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef char String[64];// string as a string

typedef struct node{
    String name;
    String phoneNumber;
    struct node *left;
    struct node *right;
} Node;

/////////////////////////////////////////////////////////////////////
Node *mallocNode(String, String);
Node *addData(Node *target_node, Node *add_node){
    if (!target_node) {// if no root, create as a root

        printf("We don't have no root.\nCreated a root!\n");
        target_node = mallocNode(add_node->name, add_node->phoneNumber);

        if (!target_node) return NULL; // malloc error

        return target_node;
    }


    Node *node = target_node;
    while(1) {
        int nameCmp = strcmp(add_node->name, node->name);
        if (nameCmp < 0) { // The case new name is lease than root
            printf("going to left node\n");
            if (node->left == NULL) { // if no left node, malloc
                printf("We don't have no child.\nCreated a child here!\n");
                node->left = mallocNode(add_node->name, add_node->phoneNumber); // add new node at left
                break;
            }
            node = node->left; // if has left, switch this to center
            printf("We have a left child n switch to left child.\n");

        } else if (nameCmp > 0) { // The case new name is bigger than root
            printf("going to right node\n");
            if (node->right == NULL) {
                printf("We don't have no child.\n Created a child here!\n");
                node->right = mallocNode(add_node->name, add_node->phoneNumber); // if no right node, malloc
                break;
            }
            node = node->right; // if has right, switch this to center
            printf("We have a right child n switch to right child.\n");

        } else if (nameCmp == 0) { // if the new name is same , skip
            printf("%s already exist\n", add_node->name);
            break;
        }
    }
    return target_node;
}

Node *mallocNode(String name, String phoneNumber) {
    Node *add = malloc(sizeof(Node));// malloc
    if (!add) {// check malloc error
        printf("Malloc Error\n");
        return NULL;
    }

    add->left = NULL;// assign, but child -> NULL
    add->right = NULL;
    strcpy(add->name, name); // assign name n phone number
    strcpy(add->phoneNumber, phoneNumber);

    return add;
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

            addData(node, &new);
        } else break;
    }
}