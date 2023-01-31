#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 64

// 基本問題１　構造体の宣言
typedef char String[N];// string as a string

typedef struct node{
    String name;
    String phoneNumber;
    struct node *left;
    struct node *right;
} Node;


// 基本問題２　要素追加関数
// 引数： target_node ... 評価するノード
// 引数： add_node ... 追加しようとしているノード
// 返り値：　構造体へのポインタ
// 動作：　target_node と add_node を比べて処理する
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


// 標準問題１　要素検索関数
// 引数： target_node ... 評価するノード
// 引数： name ... 検索する文字列
// 引数： number ... 返却する電話番号（文字列）
// 動作：　name に対応した電話番号を検索し number に代入する
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

// 標準問題２　全要素表示関数
// 引数： n ... 表示するノード
// 動作：　target_node と add_node を比べて処理する
void showAllData(Node *n){ // recursive
    if (n->left) showAllData(n->left); // left not NULL
    printf("%s: %s\n", n->name, n->phoneNumber);
    if (n->right) showAllData(n->right); // right not NULL
}


int main(){
    Node *node = NULL;

}
