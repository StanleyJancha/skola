//
// Created by standa on 4/16/26.
//

#ifndef ALG2_BSTREE_H
#define ALG2_BSTREE_H


class BSTree {
private:
    class Node {
    public:
        int value;

        Node* left = nullptr;
        Node* right = nullptr;

        Node(int value){
        this->value = value;
        }
    };

    Node* root = nullptr;

    void insert(int value, Node*& root);


public:
    void insert(int value);
    void recursion();

};


#endif //ALG2_BSTREE_H