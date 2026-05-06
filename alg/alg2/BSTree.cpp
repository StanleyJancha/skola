//
// Created by standa on 4/16/26.
//

#include "BSTree.h"


void BSTree::insert(int value) {
    this->insert(value,this->root);
}

void BSTree::insert(int value, Node*& root) {
    if (root == nullptr) {
        root = new Node(value);
        return;
    }

    if (value > root->value) {
        insert(value,root->right);
    }
    if (value < root->value) {
        insert(value,root->left);
    }
    if (value == root->value) {

    }

}
