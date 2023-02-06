#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

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

// n : how many args, target_node : root, name : search name, number : output phone number
Node *searchData(int n, Node *target_node, char name[], ...) { // updated
    char *number;
    if (n == 4) { // if has variable arguments, analize
        va_list ap; 
        va_start(ap, name);
        number = va_arg(ap, char *);
        va_end(ap);
    }

    Node *node = target_node; // duplicate
     
    while (node) { // break when node = NULL
        int cmp = strcmp(name, node->name);
        if (cmp < 0) node = node->left; // if lower than target, set to left 
        else if (cmp > 0) node = node->right; // if higher than target, set to right 
        else if (cmp == 0) { // if equal, copy
            if (n == 4) strcpy(number, node->phoneNumber); // output the phone number
            return node;
        }
    }
    if (n == 4) strcpy(number, "No number");
    return NULL;
}

void showAllData(Node *n){ // recursive
    if (n->left) showAllData(n->left); // left not NULL
    printf("%s: %s\n", n->name, n->phoneNumber);
    if (n->right) showAllData(n->right); // right not NULL
}

void readDatafromFile (Node *target_node) {
    String fName; // input File name from console
    printf("Please type file name.\n");
    scanf("%s", &fName);

    FILE *fp;
    fp = fopen(fName, "r"); // open file
    if (!fp) {// if NULL exit
        printf("Can't open %s\n", fName);
        exit(-1);
    } else printf("File opened.\n");

    String str;
    while (fgets(str, N, fp) != NULL) { // each line
        Node *new;
        strcpy(new->name, strtok(str, " ")); // split name n phoneNumber
        strcpy(new->phoneNumber, strtok(NULL, " "));

        target_node = addData(target_node, new);
    }

    fclose(fp);
    return;
}

// no child => 0, has left => 1, has right => 2, had both => 3, no name => -1
int hasChildInData(Node *target_node, char name[], Node *childNode, Node *parentNode) { 
    childNode = target_node; // duplicate
     
    while (childNode) {// search n assign parentNode pointer
        int cmp = strcmp(name, childNode->name);

        if (cmp < 0) {
            parentNode = childNode;
            childNode = childNode->left;
        } else if (cmp > 0) {
            parentNode = childNode;
            childNode = childNode->right;
        } else if (cmp == 0) {
            if (!(childNode->left) && !(childNode->right)) return 0;
            if (childNode->left && !(childNode->right)) return 1;
            if (!(childNode->left) && childNode->right) return 2;
            if (childNode->left && childNode->right) return 3;
        }
    }
    return -1 // if NULL return -1
}

// parentNode : 
void removeNoChildNode (Node *parentNode, Node *childNode) {
    if (childNode == parentNode.left) parentNode.left == NULL; // if childNode is left of parentNode -> update to NULL
    else if (childNode == parentNode.right) parentNode.right == NULL; // if childNode is right of parentNode -> update to NULL
    free(childNode);
}

// childNode : node you want to remove, grandChildNode : child of removeNode
void removeOneSideChildNode (Node *childNode, Node *grandChildNode) {
    strcpy(childNode->name, grandChildNode->name); // cpy grandChildNode to childNode
    strcpy(childNode->phoneNumber, grandChildNode->phoneNumber);
    free(grandChildNode);
}

void removeBothSideChildNode (Node *root, Node *removeNode) {
    Node *lastNode = removeNode->left; // left of the childNode
    Node *lastNodeParent = removeNode;

    while (!lastNode->right) { // find last node of the removeNode => no right node, if last
        lastNodeParent = lastNode;
        lastNode = lastNode->right;
    }

    strcpy(removeNode->name, lastNode->name); // replace name to removeNode
    strcpy(removeNode->phoneNumber, lastNode->phoneNumber); // replace phone number to removeNode

    lastNodeParent->right = NULL; // break the link
    if (lastNode->left) removeOneSideChildNode(); // if has left child
    else removeBothSideChildNode(); // if no child
}

void removeData (Node *target_node, String name) {
    Node *parentNode = NULL;
    Node *childNode = searchData(target_node, name);

    int hasChild = hasChildInData(target_node, name, childNode, parentNode);
    if (hasChild == 0) removeNoChildNode(childNode, parentNode); // no child
    else if (hasChild == 1) removeOneSideChildNode(childNode, childNode->left); // has left
    else if (hasChild == 2) removeOneSideChildNode(childNode, childNode->right); // has right
    else if (hasChild == 3) removeBothSideChildNode(target_node, childNode); // has left n right

    


}

int main(){
    Node *node = NULL; // root

    node = readDatafromFile(node);
    
    String removeName;
    printf("Please type the name whom you want to remove from the binary tree.\n");
    scanf("%s", removeName);

    removeData(node, removeName);
}
