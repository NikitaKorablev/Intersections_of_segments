//
// Created by nikita on 10/29/23.
//
#include "iostream"

#ifndef INTERSECTIONS_OF_SEGMENTS_PSEG_H
#define INTERSECTIONS_OF_SEGMENTS_PSEG_H

int r(int left = -1000, int right = 1000);

struct Point {
    double x, y;
    double z = 0.0;

    bool isLeft = false;
    int segmentIndex = -1;

    friend Point operator - (Point& p1, Point& p2);
    friend std::ostream& operator << (std::ostream& out, Point p);
    friend bool operator == (Point& p1, Point& p2);
    friend bool operator < (Point& p1, Point& p2);
    friend bool operator <= (Point& p1, Point& p2);
    friend bool operator > (Point& p1, Point& p2);
    friend bool operator >= (Point& p1, Point& p2);
};

struct Vector {
    Point p;

    int x() { return p.x; }
    int y() { return p.y; }
    int z() { return p.z; }


    friend Vector operator * (Vector& v1, Vector& v2);
};

// Класс Отрезок
class Segment {
    Point p1;
    Point p2;
    // y = kx + b уравнение прямой

//    double tmpY;
public:
    Segment();
    Segment(Point _p1, Point _p2);
    Segment(const Segment& seg);

    Point getP1() { return p1; }
    Point getP2() { return p2; }

    double calcY(double time);
//    double getY() { return tmpY; }

    friend std::ostream& operator << (std::ostream& out, Segment& seg);
    friend bool operator == (Segment seg1, Segment seg2);
};

bool intersection(Segment a, Segment b);

#endif //INTERSECTIONS_OF_SEGMENTS_PSEG_H
