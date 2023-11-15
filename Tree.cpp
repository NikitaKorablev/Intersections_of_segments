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

int Node::getCount(const Segment& s) const {
    int count = 0;
    if (seg == s) count++;
    if (l) count += l->getCount(s);
    if (r) count += r->getCount(s);
    return count;
}

bool Node::isLeaf() const {
    return l == nullptr && r == nullptr;
}

Node* Tree::search(Node* node, Segment s, double time) {
    if (node == nullptr) return nullptr;

    if (time < node->seg.getP1().x || time > node->seg.getP2().x)
        throw -1;

    if (s == node->seg) return node;

    double sKey = s.calcY(time);
    double nodeKey = node->seg.calcY(time);

    if (static_cast<int>(sKey*ERROR_RATE) == static_cast<int>(nodeKey*ERROR_RATE))
        sKey = nodeKey;

    if (sKey < nodeKey) return search(node->l, s, time);
    if (sKey >= nodeKey) return search(node->r, s, time);
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

void Tree::insert(Node* node, Segment segment) {
    if (root == nullptr) {
        root = new Node(segment);
        updateHeight(root);
        return;
    }

    double time = segment.getP1().x;
    double sKey = segment.calcY(time);
    double nodeKey = node->seg.calcY(time);

    if (time < node->seg.getP1().x || time > node->seg.getP2().x)
        throw -1;

    if (sKey < nodeKey) {
        if (node->l == nullptr) {
            node->l = new Node(segment);
            node->l->parent = node;
        }
        else {
            insert(node->l, segment);
        }
    } else if (sKey >= nodeKey) {
        if (node->r == nullptr) {
            node->r = new Node(segment);
            node->r->parent = node;
        } else {
            insert(node->r, segment);
        }
    }

    updateHeight(node);
    balance(node);
}

Node* Tree::del(Node* node, Segment seg) {
    if (node == nullptr) return node;

    double time = seg.getP2().x;
    double sKey = seg.calcY(time);
    double nodeKey = node->seg.calcY(time);

    if (time < node->seg.getP1().x || time > node->seg.getP2().x)
        throw -1;

    if (static_cast<int>(sKey*ERROR_RATE) == static_cast<int>(nodeKey*ERROR_RATE))
        sKey = nodeKey;

    if (sKey < nodeKey) node->l = del(node->l, seg);
    else if (sKey > nodeKey) node->r = del(node->r, seg);
    else {
        if (node->l == nullptr || node->r == nullptr) {
            Node* temp = node->l ? node->l : node->r;
            if (temp == nullptr) {
                delete node;
                node = nullptr;
            } else {
                std::swap(node->seg, temp->seg);
                node->l = temp->l;
                node->r = temp->r;
            }
            delete temp;
        }
        else {
            Node* minInRight = node->r->getMin();
            std::swap(node->seg, minInRight->seg);
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

int Tree::getCount(const Segment& s) {
    if (root) return root->getCount(s);
    return 0;
}

void Tree::printTree(Node *node) {
    if (node == nullptr) return;
    printTree(node->l);
    std::cout << node << std::endl;
    printTree(node->r);
}

Node* Tree::rightRotate(Node *node) {
    std::swap(node->seg, node->l->seg);
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
    std::swap(node->seg, node->r->seg);
    Node* buffer = node->l;
    node->l = node->r;

    node->r = node->l->r;
    if (node->r != nullptr) node->r->parent = node;

    node->l->r = node->l->l;

    node->l->l = buffer;
    if (node->l->l != nullptr) node->l->l->parent = node->l;

    updateHeight(node->l);
    updateHeight(node);
}

