//
// Created by nikita on 10/16/23.
//
#include "RandomSegments.h"

double r(int left, int right, int t) {
    srand(time(NULL) + t);
    return rand() % (right - left + 1) + left;
}

Segment* randCreateSeg(int left, int right) {
    int time = 0;
    double x1 = r(left, right, time++);
    double y1 = r(left, right, time++);

    double x2 = r(x1 - 10, x1 + 10, time++);
    double y2 = r(y1 - 10, y2 + 10, time++);

    if (x1 == x2 && y1 == y2) return randCreateSeg();
    else {
        Point p1(x1, y1), p2(x2, y2);
        return new Segment(p1, p2);
    }
}

void createRSegs(Segs* s, int k) {
    int i;
    for (i = 0; i < k + 1; i++) {
        Segment* seg = randCreateSeg();
        bool isInter = false;
        for (int j = 0; j < s->getLen(); j++) {
            // проверка на наличие пересечений
            if (intersection(*seg, (*s)[j])) {
                isInter = true;
                delete seg; break;
            }
        }

        if (isInter) i--;
        else s->pushBack(*seg);
    }

    auto segm = s->back();
    double l = segm.getP1().x - 1, r = segm.getP2().x + 1;

    Segment* seg = randCreateSeg();
    while (!intersection(*seg, s->back())) {
        delete seg;
        seg = randCreateSeg(l, r);
    }
    s->pushBack(*seg);
}

void rSegmentsKShift(Segs* s, int kMin, int kMax, int shift) {
    if (kMin < 0) throw -1;

    s->wrightToFile("../data/SegmentsOut.txt", true);
    for (int i = kMin; i <= kMax; i+=shift) {
//        std::cout << i << std::endl;
        createRSegs(s, i);
        s->wrightToFile("../data/SegmentsOut.txt");
        s->clear();
    }
}
void rSegmentsNShift(Segs* s, int nMin, int nMax, int shift) {
    if (nMin == 1) {
        s->pushBack(*randCreateSeg());
        return;
    } if (nMin < 1) throw -1;

    for (int i = nMin-1; i < nMax; i+=shift) {
        createRSegs(s, i-2);
    }
}