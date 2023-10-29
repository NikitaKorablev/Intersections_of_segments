//
// Created by nikita on 10/11/23.
//

#include "stack"
#include "PSeg.h"

#ifndef INTERSECTIONS_OF_SEGMENTS_TREE_H
#define INTERSECTIONS_OF_SEGMENTS_TREE_H

int ran(int left, int right);

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
    Segment nonInterSeg;

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
    void insert(const Segment& seg);
    void del(Node* node);
    void del(const Segment& seg);
    void printTree(Node* node);

    Segment getPrev(const Segment& seg);
    Segment getNext(const Segment& seg);

    Node* search(Segment* s);
    Node* search(const Segment& s);
    ~Tree() {
        delete root;
    }
};

#endif //INTERSECTIONS_OF_SEGMENTS_TREE_H
