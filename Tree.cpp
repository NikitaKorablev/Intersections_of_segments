//
// Created by nikita on 10/11/23.
//

#include "Tree.h"

int ran(int left, int right) {
    return rand() % (right - left + 1) + left;
}

Node* Node::getPrev() {
    if (parent->r == this && l == nullptr) return parent;
    else if (parent->l == this && l == nullptr) {
        Node* node = parent;
        while (node->parent != nullptr && node != node->parent->r) {
            node = node->parent;
        }
        if (node->parent == nullptr) return nullptr;
        else return node->parent;
    } else {
        Node* node = l;
        while (node->r != nullptr) node = node->r;
        return node;
    }
}

Node* Node::getNext() {
    if (parent->l == this && r == nullptr) return parent;
    else if (parent->r == this && r == nullptr) {
        Node* node = parent;
        while (node->parent != nullptr && node != node->parent->l) {
            node = node->parent;
        }
        if (node->parent == nullptr) return nullptr;
        else return node->parent;
    } else {
        Node* node = r;
        while (node->l != nullptr) node = node->l;
        return node;
    }
}

double Node::updateKey(double x) {
    lastTime = x;
    key = seg->calcY(x);
    return key;
}

Node* Tree::getMax(Node *node) {
    while (node->r != nullptr) node = node->r;
    return node;
}

Node* Tree::getMin(Node *node) {
    while (node->l != nullptr) node = node->r;
    return node;
}

Node* Tree::search(Segment* s) {
    if (root == nullptr) return nullptr;

    Node* node = root;
    while (node != nullptr) {
        if (node->seg == s) return node;
        node = node->key < node->key ? node->l : node->r;
    }
    return nullptr;
}

Node* Tree::search(const Segment& s) {
    if (root == nullptr) return nullptr;

    Node* node = root;
    while (node != nullptr) {
        if (*node->seg == s) return node;
        node = node->key < node->key ? node->l : node->r;
    }
    return nullptr;
}
//void Tree::upHeight(std::stack<Node*>* &st) {
//    while(!st->empty()) {
//        Node* node = st->top();
//        node->height = std::max(node->l->height, node->r->height) + 1;
//        st->pop();
//    }
//}

void Tree::updateHeight(Node *node) {
    node->height = std::max(node->l->height, node->r->height) + 1;
}

void Tree::insert(const Segment& segment) {
    auto* seg = new Segment(segment);
    if (root == nullptr) {
        root = new Node(seg);
        return;
    }

    double x = seg->getP1().x;
    double y = seg->getP1().y;

    Node* node = root;
    while (node != nullptr) {
        node->updateKey(x);
        if (y == node->key) throw -1;
        if (y < node->key) {
            if (node->l == nullptr) {
                node->l = new Node(seg, node);
                break;
            }
            else node = node->l;
        }
        else {
            if (node->r == nullptr) {
                node->r = new Node(seg, node);
                break;
            }
            else node = node->r;
        }
    }
    updateHeight(node);
    balance(node);
}

void Tree::del(Node* node) {
    if (node == nullptr) throw -1;

    if (node->l == nullptr || node->r == nullptr) {
        node->parent = node->l == nullptr ? node->r : node->l;
    } else {
        Node* maxInLeft = getMax(node->l);
        node->seg = maxInLeft->seg;
        maxInLeft->parent->r = nullptr;
        if (maxInLeft->parent->l == nullptr || maxInLeft->parent->r == nullptr) {
            maxInLeft->parent = maxInLeft->parent->l == nullptr ?
                    maxInLeft->parent->r : maxInLeft->parent->l;
        }
    }

    //восстанавливаем баланс
    Node* p = node;
    delete node;
    while (p->parent != nullptr) {
        p = p->parent;
        updateHeight(p);
        balance(p);
    }
}

void Tree::del(const Segment& seg) {
    del(search(seg));
}

void Tree::swap(Node *a, Node *b) { // TODO: Проверить на работоспособность
    Segment* &aS = a->seg;
    a->seg = b->seg;
    b->seg = aS;
}

int Tree::getHeight(Node *node) {
    return node == nullptr ? -1 : node->height;
}

int Tree::getBalance(Node *node) {
    return node == nullptr ? 0 : getHeight(node->r) - getHeight(node->l);
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

Segment Tree::getPrev(const Segment& seg) {
    Node* node = search(seg)->getPrev();
    if (node == nullptr) return nonInterSeg;
    else return *node->seg;
}

Segment Tree::getNext(const Segment& seg) {
    Node* node = search(seg)->getNext();
    if (node == nullptr) return nonInterSeg;
    else return *node->seg;
}

void Tree::printTree(Node *node) {
    if (node == nullptr) return;
    double x = node->lastTime;
    node->updateKey(x);
    printTree(node->l);
    std::cout << node << std::endl;
    printTree(node->r);
    std::cout << "---------------------" << std::endl;
}

void Tree::rightRotate(Node *node) {
    swap(node, node->l);
    Node* &buffer = node->r;
    node->r = node->l;
    node->l = node->r->l;
    node->r->l = node->r->r;
    node->r->r = buffer;
    updateHeight(node->r);
    updateHeight(node);
}

void Tree::leftRotate(Node *node) {
    swap(node, node->r);
    Node* &buffer = node->l;
    node->l = node->r;
    node->r = node->l->r;
    node->l->r = node->l->l;
    node->l->l = buffer;
    updateHeight(node->l);
    updateHeight(node);
}

