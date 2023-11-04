//
// Created by nikita on 10/11/23.
//

#include "Tree.h"

Node* Node::getPrev() {
    if (isLeaf()) {
        Node* node = this;
        if (node->parent == nullptr) return nullptr;
        if (node->parent->r == node) return node->parent;
        if (node->parent->l == node) {
            while (node->parent != nullptr && node->parent->l == node) {
                node = node->parent;
            }
            return node->parent;
        }
    } else {
        Node* node = this->l;
        if (node == nullptr) {
            if (parent == nullptr) return nullptr;
            if (parent->r == this) return parent;
            return nullptr;
        }
        return node->getMax();
    }
    throw -1;
}

Node* Node::getNext() {
    if (isLeaf()) {
        Node* node = this;
        if (node->parent == nullptr) return nullptr;
        if (node->parent->l == node) return node->parent;
        if (node->parent->r == node) {
            while (node->parent != nullptr && node->parent->r == node) {
                node = node->parent;
            }
            return node->parent;
        }
    } else {
        Node* node = this->r;
        if (node == nullptr) {
            if (parent == nullptr) return nullptr;
            if (parent->l == this) return parent;
            return nullptr;
        }
        return node->getMin();
    }
    throw -1;
}

Node* Node::getMax() {
    if (r == nullptr) return this;
    return r->getMax();
}

Node* Node::getMin() {
    if (l == nullptr) return this;
    return l->getMin();
}

bool Node::isLeaf() const {
    return l == nullptr && r == nullptr;
}

Node* Tree::search(Node* node, Segment s, double time) {
    if (node == nullptr)
        return nullptr;

    double sKey = s.calcY(time);
    double nodeKey = node->seg.calcY(time);

    if (sKey == nodeKey) return node;
    else if (sKey < nodeKey) return search(node->l, s, time);
    else if (sKey > nodeKey) return search(node->r, s, time);
    throw -1;
}

void Tree::updateHeight(Node *node) {
    if (node->isLeaf()) node->height = 0;
    else if (node->r != nullptr && node->l == nullptr)
        node->height = node->r->height + 1;
    else if (node->l != nullptr && node->r == nullptr)
        node->height = node->l->height + 1;
    else
        node->height = std::max(node->l->height, node->r->height) + 1;
}

Node* Tree::insert(Node* node, Segment segment) {
    if (root == nullptr) {
        root = new Node(segment);
        updateHeight(root);
        return root;
    }

    double sKey = segment.calcY(segment.getP1().x);
    double nodeKey = node->seg.calcY(segment.getP1().x);

    Node* nodeRes = nullptr;
    if (sKey <= nodeKey) {
        if (node->l == nullptr) {
            node->l = new Node(segment);
            node->l->parent = node;
            nodeRes = node->l;
        }
        else {
            nodeRes = insert(node->l, segment);
        }
    } else if (sKey > nodeKey) {
        if (node->r == nullptr) {
            node->r = new Node(segment);
            node->r->parent = node;
            nodeRes = node->r;
        } else {
            nodeRes = insert(node->r, segment);
        }
    }

    updateHeight(node);
    balance(node);
    return nodeRes;
}

Node* Tree::del(Node* node, Segment seg) {
    if (node == nullptr) return node;

    double time = seg.getP2().x;
    double sKey = seg.calcY(time);
    double nodeKey = node->seg.calcY(time);

    if (sKey < nodeKey) node->l = del(node->l, seg);
    else if (sKey > nodeKey) node->r = del(node->r, seg);
    else {
        if (node->l == nullptr || node->r == nullptr) {
            Node* temp = node->l ? node->l : node->r;
            if (temp == nullptr) {
                temp = node;
                node = nullptr;
            } else {
                node->l = temp->l;
                node->r = temp->r;
                node->seg = temp->seg;
            }
            delete temp;
        }
        else {
            Node* minInRight = node->r->getMin();
            node->seg = minInRight->seg;
            node->r = del(node->r, minInRight->seg);
        }
    }

    if (node != nullptr) {
        updateHeight(node);
        balance(node);
    }
    return node;
}

Node* Tree::remove(Segment seg) {
    root = del(root, seg);
}

void Tree::swap(Node *a, Node *b) {
    Segment aS = a->seg;
    a->seg = b->seg;
    b->seg = aS;
}

int Tree::getHeight(Node *node) {
    return node == nullptr ? -1 : node->height;
}

int Tree::getBalance(Node *node) {
    if (node == nullptr) return -1;

    int l_height = -1, r_height = -1;
    if (node->l != nullptr) l_height = getHeight(node->l);
    if (node->r != nullptr) r_height = getHeight(node->r);

    return r_height - l_height;
}

void Tree::balance(Node *node) {
    int b = getBalance(node);
    if (b == -2) { // перегрузка влево
        if (getBalance(node->l) == 1) leftRotate(node->l);
        rightRotate(node);
    }
    else if (b == 2) { // перегрузка вправо
        if (getBalance(node->r) == -1) rightRotate(node->r);
        leftRotate(node);
    }
}

Segment Tree::getPrev(Node* node) {
    if (node == nullptr) return nonInterSeg1;
    Node* node2 = node->getPrev();
    if (node2 == nullptr) return nonInterSeg1;
    else return node2->seg;
}

Segment Tree::getNext(Node* node) {
    if (node == nullptr) return nonInterSeg2;
    Node* node2 = node->getNext();
    if (node2 == nullptr) return nonInterSeg2;
    else return node2->seg;
}

void Tree::printTree(Node *node) {
    if (node == nullptr) return;
    printTree(node->l);
    std::cout << node << std::endl;
    printTree(node->r);
    std::cout << "---------------------" << std::endl;
}

void Tree::rightRotate(Node *node) {
    swap(node, node->l);
    Node* buffer = node->r;
    node->r = node->l;

    node->l = node->r->l;
    if (node->l != nullptr) node->l->parent = node;

    node->r->l = node->r->r;

    node->r->r = buffer;
    if (node->r->r != nullptr) node->r->r->parent = node->r;

    updateHeight(node->r);
    updateHeight(node);
}

void Tree::leftRotate(Node *node) {
    swap(node, node->r);
    Node* buffer = node->l;
    node->l = node->r;

    node->r = node->l->r;
    if (node->r) node->r->parent = node;

    node->l->r = node->l->l;

    node->l->l = buffer;
    if (node->l->l) node->l->l->parent = node->l;

    updateHeight(node->l);
    updateHeight(node);
}

