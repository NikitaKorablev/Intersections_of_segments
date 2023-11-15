//
// Created by nikita on 10/29/23.
//
#include "iostream"

#ifndef INTERSECTIONS_OF_SEGMENTS_PSEG_H
#define INTERSECTIONS_OF_SEGMENTS_PSEG_H

//#define ERROR_RATE 0.000001
#define ERROR_RATE 100000000

int r(int left = -1000, int right = 1000);

struct Point {
    double x, y;
    double z = 0.0;

//    Point(Point const &point);

    bool isLeft = false;
    bool beforeK(int k = -1) const {
        return k != -1 && segmentIndex <= k + 2;
    }
    int segmentIndex = -1;

    friend Point operator - (Point& p1, Point& p2);
    friend std::ostream& operator << (std::ostream& out, Point p);
//    Point& operator = (const Point& p);
    friend bool operator == (Point& p1, Point& p2);
    friend bool operator < (Point& p1, Point& p2);
    friend bool operator <= (Point& p1, Point& p2);
    friend bool operator > (Point& p1, Point& p2);
    friend bool operator >= (Point& p1, Point& p2);
};

struct Vector {
    Point p;

    double x() { return p.x; }
    double y() { return p.y; }
    double z() { return p.z; }


    friend Vector operator * (Vector& v1, Vector& v2);
};

// Класс Отрезок
class Segment {
    Point p1;
    Point p2;

    double k;
    double b;
public:
    Segment();
    Segment(Point _p1, Point _p2);
    Segment(const Segment& seg);

    void calcCoef();
    void setSegIndexForPoints(int ind);

    Point getP1() const { return p1; }
    Point getP2() const { return p2; }

    double calcY(double time);

    friend std::ostream& operator << (std::ostream& out, Segment& seg);
    friend std::ostream& operator << (std::ostream& out, const Segment& seg);
    friend bool operator == (Segment seg1, Segment seg2);
    friend bool operator != (Segment seg1, Segment seg2);
};


#endif //INTERSECTIONS_OF_SEGMENTS_PSEG_H
