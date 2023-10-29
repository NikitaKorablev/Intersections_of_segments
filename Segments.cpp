//
// Created by nikita on 10/8/23.
//
#include "Segments.h"



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

int Segs::partition(int left, int right) {
    Point pivot = points[right];
    int wall = left;
    for (int i = left; i < right-1; i++) {
        if (points[i] <= pivot) {
            std::swap(points[i], points[wall]);
            wall++;
        }
    }
    return wall;
}

void Segs::sortPoints(int left, int right) {
    if (left == -1 || right == -1) {
        left = 0; right = points.size();
    }

    if (right - left == 1) return;
    int wall = partition(left, right);
    sortPoints(left, wall);
    sortPoints(wall, right);
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

bool Segs::intersection_naive() {
    bool res = false;
    int len = segments.size();
    for (int i = 0; i < len-1; i++) {
        for (int j = i + 1; j < len; j++) {
            if (intersection(segments[i], segments[j])) {
                res = true;
                break;
            }
        }
        if (res) break;
    }
    return res;
}

bool Segs::intersection_effective() {
    Tree tree; sortPoints();
    bool inter = false;

    for (auto p : points) {
        Segment s = segments[p.segmentIndex];
        if (p.isLeft) {
            tree.insert(s);
            Segment s1 = tree.getPrev(s);
            Segment s2 = tree.getNext(s);
            if (intersection(s, s1) || intersection(s, s2)) {
                inter = true;
                break;
            }
        } else {
            Segment s1 = tree.getPrev(s);
            Segment s2 = tree.getNext(s);
            if (intersection(s1, s2)) {
                inter = true;
                break;
            }
            tree.del(s);
        }
    }
    return inter;
}