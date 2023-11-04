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

bool intersection(const Segment& a, const Segment& b);

class Segs {
    std::vector<Segment> segments;
    std::vector<Point> points;

    int partition(int l, int r);
    Segment* randCreateSeg(int left = -1000000, int right = 1000000,
                           int down = 1000000, int up = 1000000);
    Segment* randSegsByLength(double len);
public:
    void sTest() { sortPoints(0, points.size()-1); }

    Segs(){};
    Segs(const Segs& s);

    void rSetByPoints(int n, int k = -1);
    void rSetByLength(double length, int n);

    int getLen() { return segments.size(); }
    int getPointLen() {return points.size(); }
    void pushBack(const Segment& seg);
//    void pushBackPoint(Point p) { points.push_back(p); }
    void sortPoints(int l, int r);

    void readFromFile(const std::string& filePath);
    void saveToFile(const std::string& filePath, bool clearFile = false);
    void printS();
    void clear();

    bool intersection_naive();
    bool intersection_effective();

    Segment front() { return segments.front(); }
    Segment back() { return segments.back(); }

    friend std::ostream& operator << (std::ostream& out, const std::vector<Point>& vec);

    Segment operator [] (int i) {
        if (i < 0 || i >= segments.size()) {
            throw -1;
        }
        return segments[i];
    }
};

#endif //AISD_SECTION_H
