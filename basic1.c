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

int main () {
    Node test = {"John", "048-352-9110"};
    Node test2 = {"Micheal", "0120-107-929"};
    Node test3 = {"Mike", "0120-333-906", &test, &test2};
    printf("The content is\nParent:%s(PhoneNumber is %s),\nLeft child is %s(PhoneNumber is %s),\nRight child is %s(PhoneNumber is %s)\n", test3.name, test3.phoneNumber, test3.left->name, test3.left->phoneNumber, test3.right->name, test3.right->phoneNumber);
}