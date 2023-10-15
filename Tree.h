//
// Created by nikita on 10/11/23.
//

#ifndef INTERSECTIONS_OF_SEGMENTS_TREE_H
#define INTERSECTIONS_OF_SEGMENTS_TREE_H

#include "stack"
#include "Segments.h"

struct Node {
//    int value;
    double key;
    double lastTime;
    int height;
    Node* parent;
    Node* l;
    Node* r;
    Segment* seg;
    explicit Node(Segment* segment, Node* left = nullptr,
                  Node* right = nullptr, Node* _parent = nullptr,
                  int h = -1) :
                  seg(segment), height(h), l(left), r(right){};

    Node* getPrev();
    Node* getNext();

    double updateKey(double x);

    ~Node() {
        delete parent;
        delete l;
        delete r;
        delete seg;
    }
};

class Tree {
    Node* root;

    Node* getMax(Node* node);
    Node* getMin(Node* node);
    void swap(Node* a, Node* b);
    void updateHeight(Node* node);
    int getHeight(Node* node);
    int getBalance(Node* node);
    void rightRotate(Node* node);
    void leftRotate(Node* node);
    void balance(Node* node);
public:
    Tree() { root = nullptr; }
    void insert(Segment* seg);
    void del(Segment* seg);
    void printTree(Node* node);

    Node* search(Segment* s);
    ~Tree() {
        delete root;
    }
};

#endif //INTERSECTIONS_OF_SEGMENTS_TREE_H
