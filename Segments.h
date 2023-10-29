//
// Created by nikita on 10/8/23.
//
#include "vector"
#include "fstream"
#include "sstream"
#include "string"
#include <cmath>
#include "Tree.h"

#ifndef AISD_SECTION_H
#define AISD_SECTION_H


class Segs {
    std::vector<Segment> segments;
    std::vector<Point> points;

    int partition(int l, int r);
public:
    Segs(){};
    Segs(const Segs& s);

    int getLen() { return segments.size(); }
    void pushBack(Segment seg) { segments.push_back(seg); };
    void pushBackPoint(Point p) { points.push_back(p); }
    void sortPoints(int l = -1, int r = -1);

    void readFromFile(const std::string& filePath);
    void saveToFile(const std::string& filePath, bool clearFile = false);
    void printS();
    void clear();

    bool intersection_naive();
    bool intersection_effective();

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
