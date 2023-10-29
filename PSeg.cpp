//
// Created by nikita on 10/29/23.
//

#include "PSeg.h"

int r(int left, int right) {
    return rand() % (right - left + 1) + left;
}

std::ostream& operator << (std::ostream& out, Point p) {
    out << p.x << " " << p.y;
    return out;
}

Point operator - (Point& p1, Point& p2) {
    Point p(p2.x - p1.x, p2.y - p1.y);
    return p;
}

bool operator < (Point& p1, Point& p2) {
    if (p1.x < p2.x) return true;
    return false;
}

bool operator <= (Point& p1, Point& p2) {
    if (p1.x == p2.x) {
        if (p1.isLeft) return false;
        return true;
    }

    if (p1.x < p2.x) return true;
    return false;
}

bool operator > (Point& p1, Point& p2) {
    if (p1.x > p2.x) return true;
    return false;
}

bool operator >= (Point& p1, Point& p2) {
    if (p1.x > p2.x) return true;
    return false;
}

bool operator == (Point& p1, Point& p2) {
    if (p1.x == p2.x &&
        p1.y == p2.y &&
        p1.z == p2.z) return true;

    return false;
}

//-----------------Vector-class-----------------

Vector operator * (Vector& v1, Vector& v2) {
    int x = v1.y()*v2.z() - v1.z()*v2.y();
    int y = v1.x()*v2.z() - v1.z()*v2.x();
    int z = v1.x()*v2.y() - v1.y()*v2.x();

    return Vector(Point(x, y, z));
}

//-----------------Segment-class-----------------

Segment::Segment() {
    p1 = Point(r(500, 600), r(500, 600));
    p2 = Point(r(500, 600), r(500, 600));
}

Segment::Segment(Point _p1, Point _p2)  {
    if (_p1.x == _p2.x) {
        p1 = _p1;
        p2 = _p2;
        return;
    }
    if (_p1.x < _p2.x) {
        p1 = _p1;
        p2 = _p2;
    } else {
        p1 = _p2;
        p2 = _p1;
    }
    p1.isLeft = true;
}

Segment::Segment(const Segment& seg) {
    p1 = seg.p1;
    p2 = seg.p2;
}

double Segment::calcY(double time) { //calcY
    if (p1.x == p2.x) throw -1;

    double k = (p2.y - p1.y) / (p2.x - p1.x);
    double b = p1.y - p1.x * ((p2.y - p1.y) / (p2.x - p1.x));
    return k * time + b;
}

std::ostream& operator << (std::ostream& out, Segment& seg) {
    out << seg.getP1() << ", " << seg.getP2();
    return out;
}

bool operator == (Segment seg1, Segment seg2) {
    if (seg1.p1 == seg2.p1 &&
        seg1.p2 == seg2.p2) return true;

    return false;
}
