//
// Created by nikita on 10/16/23.
//
#include "RandomSegments.h"

void t1() {
    std::string fileDir = "../data/test1.txt";
    Segs* s = new Segs;

    for (int i = 1; i <= 10001; i+=100) {
        std::cout << "i = "<< i << std::endl;
//        createRSegsByPoints(s, i);
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
//        createRSegsByPoints(s, 10003, i);
        if (i == 1) s->saveToFile(fileDir, true);
        else s->saveToFile(fileDir);
        s->clear();
    }
    std::cout << "T2 end work" << std::endl;
    delete s;
}

void t3() {
    std::string fileDir = "../data/test3.txt";
    Segs* s = new Segs;
    double r = 0.001;

    for (int n = 1; n < 201; n+=100) {
        std::cout << "n = " << n << std::endl;
//        createRSegsByLength(s, r, n);
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
//        createRSegsByLength(s, r, n);
        if (r == 0.0001) s->saveToFile(fileDir, true);
        else s->saveToFile(fileDir);
        r+=0.0001;
    }

    std::cout << "T3 end work" << std::endl;
    delete s;
}