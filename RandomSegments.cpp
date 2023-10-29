//
// Created by nikita on 10/16/23.
//
#include "RandomSegments.h"



Segment* randCreateSeg(int left, int right, int down, int up) {
//    std::cout << "call" << std::endl;
    int x1 = r(left, right);
    int y1 = r(down, up);

    int x2 = r(left, right);
    int y2 = r(down, up);

    while (x2 == x1) { x2 = r(left, right); }
    while (y2 == y1) { y2 = r(down, up); }

    Point p1(x1, y1), p2(x2, y2);
    return new Segment(p1, p2);
}

void createRSegsByPoints(Segs* &s, int n, int k) {
    if (n == 0) return;

    if (n == 1) {
        s->pushBack(*randCreateSeg());
        return;
    }
    if (n < 0 || k < -1 || k >= n-1) throw -1;

    if (k == -1) k = r(1, n-1);
    int i;
    for (i = 0; i < k + 1; ++i) {

        Segment* seg = randCreateSeg();
        bool isInter = false;

        // проверка на отсутствие пересечений
        for (int j = 0; j < s->getLen(); j++) {
            if (intersection(*seg, (*s)[j])) {
                isInter = true;
                break;
            }
        }

        if (isInter) i--;
        else s->pushBack(*seg);
        delete seg;
    }

    auto segm = s->back();

    // Для упрощения поиска отрезка пересекающего последний добавленный отрезок
    // ограничим область поиска
//    int l = segm.getP1().x, r = segm.getP2().x;
//    int up = std::max(segm.getP1().y, segm.getP2().y);
//    int down = std::min(segm.getP1().y, segm.getP2().y);

    Segment* seg = randCreateSeg();
    while (!intersection(*seg, segm)) {
        delete seg;
        seg = randCreateSeg();
    }
    s->pushBack(*seg); i++;
    delete seg;

    while (i < n-1) {
        s->pushBack(*randCreateSeg());
        i++;
    }

}

void t1() {
    std::string fileDir = "../data/test1.txt";
    Segs* s = new Segs;

    for (int i = 1; i <= 10001; i+=100) {
        std::cout << "i = "<< i << std::endl;
        createRSegsByPoints(s, i);
        if (i == 1) s->saveToFile(fileDir, true);
        else s->saveToFile(fileDir);
        s->clear();
    }
    std::cout << "T1 end work" << std::endl;
    delete s;
}

void t2() {
    std::string fileDir = "../data/test2.txt";
    Segs* s = new Segs;

    for (int i = 1; i <= 10001; i+=100) {
        std::cout << "i = " << i << std::endl;
        createRSegsByPoints(s, 10003, i);
        if (i == 1) s->saveToFile(fileDir, true);
        else s->saveToFile(fileDir);
        s->clear();
    }
    std::cout << "T2 end work" << std::endl;
    delete s;
}

Segment* randSegsByLength(double len) {
    int angle = r(-90, 90);
    double middleX = r(-1, 1), middleY = r(-1, 1);
//    std::cout << "angle = " << angle << std::endl;
//    std::cout << "x, y: " << middleX  << " " << middleY << std::endl;

    double x1, x2;
    double y1, y2;

    double c = len/2;
    if (angle == 0) {
        x1 = middleX - c; x2 = middleX + c;
        y1 = middleY; y2 = middleY;
    } else if (angle == 90 || angle == -90) {
        x1 = middleX; x2 = middleX;
        y1 = middleY - c; y2 = middleY + c;
    } else {
        double k = angle == 45 ? 1 : tan(angle*M_PI / 180);
        double b = middleY - k*middleX;

        double D = std::pow(2*(middleX + k*(middleY-b)), 2) -
                   4*(1+k*k)*(middleX*middleX + (middleY-b)*(middleY-b) - c*c);
        double sqrtD = std::sqrt(D);

        x1 = (2*(middleX + k*(middleY-b)) - sqrtD) / (2*(1+k*k));
        x2 = (2*(middleX + k*(middleY-b)) + sqrtD) / (2*(1+k*k));

        y1 = k*x1 + b;
        y2 = k*x2 + b;
    }

    Point p1(x1, y1), p2(x2, y2);
    return new Segment(p1, p2);
}

void createRSegsByLength(Segs* &segments, double length, int n) {
    segments->clear();
    Segment* seg;
    for (int i = 0; i < n; i++) {
        seg = randSegsByLength(length);
        segments->pushBack(*seg);
        delete seg;
    }
}

void t3() {
    std::string fileDir = "../data/test3.txt";
    Segs* s = new Segs;
    double r = 0.001;

    for (int n = 1; n < 201; n+=100) {
        std::cout << "n = " << n << std::endl;
        createRSegsByLength(s, r, n);
        if (n == 1) s->saveToFile(fileDir, true);
        else s->saveToFile(fileDir);
    }
    std::cout << "T3 end work" << std::endl;
    delete s;
}

void t4() {
    std::string fileDir = "../data/test4.txt";
    Segs* s = new Segs;
    int n = 10000; double r = 0.0001;

    while (r < 0.01) {
        std::cout << "len = " << r << std::endl;
        createRSegsByLength(s, r, n);
        if (r == 0.0001) s->saveToFile(fileDir, true);
        else s->saveToFile(fileDir);
        r+=0.0001;
    }

    std::cout << "T3 end work" << std::endl;
    delete s;
}