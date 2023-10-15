//
// Created by nikita on 10/8/23.
//
#include "Segments.h"


std::ostream& operator << (std::ostream& out, Point p) {
    out << p.x << " " << p.y;
    return out;
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

    k = (p2.y - p1.y) / (p2.x - p1.x);
    b = p1.y - p1.x * ((p2.y - p1.y) / (p2.x - p1.x));
}

Segment::Segment(const Segment& seg) {
    p1 = seg.p1;
    p2 = seg.p2;
    k = seg.k;
    b = seg.b;
}

double Segment::calcY(double time) { //calcY
    return k * time + b;
}

std::ostream& operator << (std::ostream& out, Segment& seg) {
    out << seg.getP1() << ", " << seg.getP2();
    return out;
}

Segs::Segs(const Segs& s) {
    segments = s.segments;
}

//-----------------Segs-class-----------------

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
    }
}

void Segs::printS() {
    for (auto &element: segments) {
        std::cout << element << std::endl;
        std::cout << "----------------" << std::endl;
    }
}