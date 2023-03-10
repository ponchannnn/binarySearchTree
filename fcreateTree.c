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
    if (!target_node) {// if no root, create as a root
        target_node = mallocNode(add_node->name, add_node->phoneNumber);

        if (!target_node) return NULL; // malloc error
        return target_node;
    }

    Node *node = target_node;
    while(1) {
        int nameCmp = strcmp(add_node->name, node->name);
        if (nameCmp < 0) { // The case new name is lease than root
            if (!node->left) { // if no left node, malloc
                node->left = mallocNode(add_node->name, add_node->phoneNumber); // add new node at left
                break;
            }
            node = node->left; // if has left, switch this to center

        } else if (nameCmp > 0) { // The case new name is bigger than root
            if (!node->right) {
                node->right = mallocNode(add_node->name, add_node->phoneNumber); // if no right node, malloc
                break;
            }
            node = node->right; // if has right, switch this to center

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


void searchData(Node *target_node, char name[], char number[]) {
    Node *node = target_node; // duplicate
     
    while (node) { // break when node = NULL
        int cmp = strcmp(name, node->name);
        if (cmp < 0) node = node->left; // if lower than target, set to left 
        else if (cmp > 0) node = node->right; // if higher than target, set to right 
        else if (cmp == 0) strcpy(number, node->phoneNumber); // if equal, copy
    }
    strcpy(number, "No number");
}

void showAllData(Node *n){ // recursive
    if (n->left) showAllData(n->left); // left not NULL
    printf("%s: %s\n", n->name, n->phoneNumber);
    if (n->right) showAllData(n->right); // right not NULL
}

Node *readDatafromFile (Node *target_node) {
    String fName; // input File name from console
    printf("Please type file name.\n");
    scanf("%s", fName);
    FILE *fp;
    fp = fopen(fName, "r"); // open file
    if (!fp) {// if NULL exit
        printf("Can't open %s\n", fName);
        exit(-1);
    } else printf("File opened.\n");

    String str;
    while (fgets(str, N, fp)) { // each line (still fgets => NULL)
        Node new;
        strcpy(new.name, strtok(str, " ")); // split name n phoneNumber
        strcpy(new.phoneNumber, strtok(NULL, " "));
        target_node = addData(target_node, &new);
    }

    fclose(fp);
    return target_node;
}

int main(){
    Node *node = NULL; // root
    node = readDatafromFile(node);
    showAllData(node);
}
