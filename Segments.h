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

    friend std::ostream& operator << (std::ostream& out, Point p);
};

// Класс Отрезок
class Segment {
    Point p1;
    Point p2;
    // y = kx + b уравнение прямой
    double k;
    double b;

//    double tmpY;
public:
    Segment(Point _p1, Point _p2);
    Segment(const Segment& seg);

    Point getP1() { return p1; }
    Point getP2() { return p2; }

    double getK() { return k; }
    double getB() { return b; }

    double calcY(double time);
//    double getY() { return tmpY; }

    friend std::ostream& operator << (std::ostream& out, Segment& seg);
};

class Segs {
    std::vector<Segment> segments;
public:
    Segs(){};
    Segs(const Segs& s);

    int getLen() { return segments.size(); }
    void readFromFile(const std::string& filePath);
    void printS();

    Segment& operator [] (int i) {
        if (i < 0 || i >= segments.size()) {
            throw -1;
        }
        return segments[i];
    }
};
#endif //AISD_SECTION_H
