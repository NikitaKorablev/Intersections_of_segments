//
// Created by nikita on 10/11/23.
//

#include "Intersection.h"
bool BaseInter::intersection(Segment a, Segment b) {
    Point aP1 = a.getP1(); Point bP1 = b.getP1();
    Point aP2 = a.getP2(); Point bP2 = b.getP2();
    if (a.getK() == b.getK() && a.getB() == b.getB()) {
        if (aP1.x <= bP1.x && bP1.x <= aP2.x || aP1.x <= bP2.x && bP2.x <= aP2.x) return true;
        else return false;
    } else if (a.getK() == b.getK()) {
        return false;
    } else {
        double x = (b.getB() - a.getB()) / (a.getK() - b.getK());
        if (!(aP1.x <= x && x <= aP2.x) || !(bP1.x <= x && x <= bP2.x)) return false;
        else return true;
    }
}

bool Naive::intersection_naive(Segment *&seg1, Segment *&seg2)  {
    bool res = false;
    int len = segments.getLen();
    for (int i = 0; i < len-1; i++) {
        for (int j = i + 1; j < len; j++) {
            if (intersection(segments[i], segments[j])) {
                res = true;

                seg1 = new Segment(segments[i]);
                seg2 = new Segment(segments[j]);

                break;
            }
        }
        if (res) break;
    }
    return res;
}



