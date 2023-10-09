//
// Created by nikita on 10/8/23.
//
#include "vector"
#include "iostream"
#include "fstream"
#include "sstream"
#include "string"

#ifndef AISD_SECTION_H
#define AISD_SECTION_H

struct Point {
    double x, y;
};

// Класс Отрезок
class Segment {
    Point p1;
    Point p2;
    // y = kx + b уравнение прямой
    double k;
    double b;
public:
    Segment(Point _p1, Point _p2) {
        if (_p1.x <= _p2.x) {
            p1 = _p1;
            p2 = _p2;
        } else {
            p1 = _p2;
            p2 = _p1;
        }

        k = (p2.y - p1.y) / (p2.x - p1.x);
        b = p1.y - p1.x * ((p2.y - p1.y) / (p2.x - p1.x));
    };

    Point getP1() { return p1; }
    Point getP2() { return p2; }

    double getK() { return k; }
    double getB() { return b; }
};

// Множество для хранения отрезков
class S {
    std::vector<Segment> s;
    int len;

    bool intersection(Segment a, Segment b);
public:
    S() { len = 0; };

    void appendSection(Segment sec);
    bool intersection_naive(Segment* seg1 = nullptr, Segment* seg2 = nullptr);
    void readFromFile(const std::string& filePath);
};



#endif //AISD_SECTION_H
