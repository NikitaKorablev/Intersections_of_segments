//
// Created by nikita on 10/8/23.
//
#include "vector"
#include "iostream"
#include "fstream"
#include "sstream"
#include "string"
#include <cmath>

#ifndef AISD_SECTION_H
#define AISD_SECTION_H

struct Point {
    int x, y;
    int z = 0;

    friend std::ostream& operator << (std::ostream& out, Point p);
};

struct Vector {
    Point p;

    int x() { return p.x; }
    int y() { return p.y; }
    int z() { return p.z; }

    friend Point operator - (Point& p1, Point& p2);
    friend Vector operator * (Vector& v1, Vector& v2);
};

// Класс Отрезок
class Segment {
    Point p1;
    Point p2;
    // y = kx + b уравнение прямой

//    double tmpY;
public:
    Segment(Point _p1, Point _p2);
    Segment(const Segment& seg);

    Point getP1() { return p1; }
    Point getP2() { return p2; }

    double calcY(double time);
//    double getY() { return tmpY; }

    friend std::ostream& operator << (std::ostream& out, Segment& seg);
};

bool intersection(Segment a, Segment b);

class Segs {
    std::vector<Segment> segments;
public:
    Segs(){};
    Segs(const Segs& s);

    int getLen() { return segments.size(); }
    void pushBack(Segment seg) { segments.push_back(seg); };
    void readFromFile(const std::string& filePath);
    void wrightToFile(const std::string& filePath, bool clearFile = false);
    void printS();
    void clear();

    Segment front() { return segments.front(); }
    Segment back() { return segments.back(); }

    Segment operator [] (int i) {
        if (i < 0 || i >= segments.size()) {
            throw -1;
        }
        return segments[i];
    }
};
#endif //AISD_SECTION_H
