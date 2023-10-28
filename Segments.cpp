//
// Created by nikita on 10/8/23.
//
#include "Segments.h"

std::ostream& operator << (std::ostream& out, Point p) {
    out << p.x << " " << p.y;
    return out;
}

//-----------------Vector-class-----------------

Point operator - (Point& p1, Point& p2) {
    return Point(p2.x - p1.x, p2.y - p1.y);
}

Vector operator * (Vector& v1, Vector& v2) {
    int x = v1.y()*v2.z() - v1.z()*v2.y();
    int y = v1.x()*v2.z() - v1.z()*v2.x();
    int z = v1.x()*v2.y() - v1.y()*v2.x();

    return Vector(Point(x, y, z));
}

bool operator == (Point& p1, Point& p2) {
    if (p1.x == p2.x &&
        p1.y == p2.y &&
        p1.z == p2.z) return true;

    return false;
}

//-----------------Segment-class-----------------

Segment::Segment(Point _p1, Point _p2)  {
    if (_p1.x <= _p2.x) {
        p1 = _p1;
        p2 = _p2;
    } else {
        p1 = _p2;
        p2 = _p1;
    }
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

//-----------------Segs-class-----------------

Segs::Segs(const Segs& s) {
    segments = s.segments;
}

bool intersection(Segment a, Segment b) {
    Point aP1 = a.getP1(); Point bP1 = b.getP1();
    Point aP2 = a.getP2(); Point bP2 = b.getP2();
    Vector vec1(aP2 - aP1), vec2(bP2 - bP1);

    Vector v1(bP1 - aP1), v2(bP2 - aP1);
    Vector prod1(vec1 * v1), prod2(vec1 * v2);

    if (prod1.z() > 0 && prod2.z() > 0 ||
        prod1.z() < 0 && prod2.z() < 0) return false;

    Vector v3(aP1 - bP1), v4(aP2 - bP1);
    prod1 = vec2 * v3; prod2 = vec2 * v4;

    if (prod1.z() > 0 && prod2.z() > 0 ||
        prod1.z() < 0 && prod2.z() < 0) return false;

    return true;
}

void Segs::readFromFile(const std::string &filePath) {
    std::ifstream file;
    file.open(filePath);
    std::string res;
    if (file.is_open()) {
        while(getline(file, res)) {
            std::vector<int> coordinates;
            std::string element;
            std::stringstream elemInLine(res);
            while (getline(elemInLine, element, ' ')) {
                coordinates.push_back(stoi(element));
            }

            Segment seg(Point(coordinates[0], coordinates[1]),
                        Point(coordinates[2], coordinates[3]));

            segments.push_back(seg);
        }
        file.close();
    }
}

void Segs::saveToFile(const std::string& filePath, bool clearFile) {
    if (filePath == "") throw -1;

    std::ofstream file;
    if (clearFile) file.open(filePath);
    else file.open(filePath, std::ios::app);

    if (file.is_open()) {
        for (auto &element: segments) {
            file << element << std::endl;
        }
        file << "~==~" << std::endl;
        file.close();
    } else {
        std::exit(-1);
    }
}

void Segs::printS() {
    for (auto &element: segments) {
        std::cout << element << std::endl;
        std::cout << "----------------" << std::endl;
    }
}

void Segs::clear() {
    segments.clear();
}