//
// Created by nikita on 10/29/23.
//

#include "PSeg.h"

int r(int left, int right) {
    return rand() % (right - left + 1) + left;
}

//Point::Point(Point const &point) {
//    x = point.x;
//    y = point.y;
//    z = point.z;
//
//    isLeft = point.isLeft;
//    segmentIndex = point.segmentIndex;
//}

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

//Point& Point::operator = (const Point& p) {
//    x = p.x;
//    y = p.y;
//    z = p.z;
//
//    isLeft = p.isLeft;
//    segmentIndex = p.segmentIndex;
//    return *this;
//}

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
    double x = v1.y()*v2.z() - v1.z()*v2.y();
    double y = v1.x()*v2.z() - v1.z()*v2.x();
    double z = v1.x()*v2.y() - v1.y()*v2.x();

    return Vector(Point(x, y, z));
}

//-----------------Segment-class-----------------

Segment::Segment() {
    k = 0; b = 0;
//    currentX = -1;
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
    calcCoef();
}

Segment::Segment(const Segment& seg) {
    p1 = seg.p1;
    p2 = seg.p2;
    k = seg.k;
    b = seg.b;
}

void Segment::calcCoef() {
    double a1 = p2.y - p1.y;
    double a2 = p2.x - p1.x;

    k = (a1) / (a2);

    b = (p1.y*p2.x - p1.x*p2.y) / (a2);
}

void Segment::setSegIndexForPoints(int ind) {
    p1.segmentIndex = ind;
    p2.segmentIndex = ind;
}

double Segment::calcY(double time) { //calcY
    calcCoef();
    return k * time + b;
}

std::ostream& operator << (std::ostream& out, Segment& seg) {
    out << seg.getP1() << ", " << seg.getP2();
    return out;
}

std::ostream& operator << (std::ostream& out, const Segment& seg) {
    out << seg.getP1() << ", " << seg.getP2();
    return out;
}

bool operator == (Segment seg1, Segment seg2) {
    return seg1.p1 == seg2.p1 && seg1.p2 == seg2.p2;
}

bool operator != (Segment seg1, Segment seg2) {
    return !(seg1 == seg2);
}