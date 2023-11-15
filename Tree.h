//
// Created by nikita on 10/11/23.
//

#include "stack"
#include "PSeg.h"

#ifndef INTERSECTIONS_OF_SEGMENTS_TREE_H
#define INTERSECTIONS_OF_SEGMENTS_TREE_H

struct Node {
    int height;
    Node* parent;
    Node* l;
    Node* r;
    Segment seg;
    explicit Node(const Segment& segment, Node* _parent = nullptr,
                  Node* left = nullptr, Node* right = nullptr, int h = 0) :
                  seg(segment), height(h), l(left), r(right),
                  parent(_parent){};

    Node* getPrev();
    Node* getNext();
    Node* getMax();
    Node* getMin();
    int getCount(const Segment& s) const;

    bool isLeaf() const;

    ~Node() {
        delete l;
        delete r;
    }
};

class Tree {
    Node* root;
    Segment nonInterSeg1;
    Segment nonInterSeg2;

    static void swap(Node* a, Node* b);
    static void updateHeight(Node* node);
    int getHeight(Node* node);
    int getBalance(Node* node);
    static Node* rightRotate(Node* node);
    static void leftRotate(Node* node);
    void balance(Node* node);
public:
    Tree() {
        root = nullptr;
        nonInterSeg1 = Segment(Point(500, 600),
                               Point(501, 601));
        nonInterSeg2 = Segment(Point(-500, -600),
                               Point(-501, -601));
    }

    Node* getRoot() { return root; }
    Segment getPrev(Node* node);
    Segment getNext(Node* node);

    int getCount(const Segment& s);

    void insert(Node* node, Segment seg);
    Node* del(Node* node, Segment seg);
    Node* remove(Segment seg);
    Node* search(Node* node, Segment s, double time);

    void printTree(Node* node);
};

#endif //INTERSECTIONS_OF_SEGMENTS_TREE_H
