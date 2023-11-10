//
// Created by nikita on 10/27/23.
//

#include "Tests.h"

void startTest(Segs* s, std::ofstream& file, double i) {
    if (file.is_open()) {
        auto start_time = std::chrono::high_resolution_clock::now();
        std::cout << s->intersectionNaive() << std::endl;
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

        file << i << " " << duration.count();

        start_time = std::chrono::high_resolution_clock::now();
        s->sortPoints(0, s->getPointLen() - 1);
        end_time = std::chrono::high_resolution_clock::now();
        auto sortDuration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);


        start_time = std::chrono::high_resolution_clock::now();
        s->intersectionEffective();
        end_time = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

        file << " " << sortDuration.count() << " " << duration.count() << std::endl;
    }
}


void test1(const std::string& fileDir) {
    if (fileDir.empty()) throw -1;

    Segs* s = new Segs;
    std::ofstream file;
    file.open(fileDir);

    for (int i = 1; i <= 10001; i+=100) {
        std::cout << "i = "<< i << std::endl;
        s->rSetByPoints(i);
        startTest(s, file, i);
        s->clear();
    }

    file.close();
    delete s;
}

void test2(const std::string& fileDir) {
    if (fileDir.empty()) throw -1;

    Segs* s = new Segs;
    std::ofstream file;
    file.open(fileDir);

    for (int i = 1; i <= 10001; i+=100) {
        std::cout << "k = "<< i << std::endl;
        s->rSetByPoints(10003, i);
        startTest(s, file, i);
        s->clear();
    }

    file.close();
    delete s;
}

void test3(const std::string& fileDir) {
    if (fileDir.empty()) throw -1;

    Segs* s = new Segs;
    std::ofstream file;
    file.open(fileDir);

    for (int n = 1; n <= 10001; n+=100) {
        std::cout << "n = "<< n << std::endl;
        s->rSetByLength(0.001, n);
        startTest(s, file, n);
        s->clear();
    }

    file.close();
    delete s;
}

void test4(const std::string& fileDir) {
    if (fileDir.empty()) throw -1;

    Segs* s = new Segs;
    std::ofstream file;
    file.open(fileDir);

    double r = 0.001;
    while (r <= 0.01) {
        std::cout << "r = "<< r << std::endl;
        s->rSetByLength(r, 10000);
        startTest(s, file, r);
        s->clear();

        r+=0.0001;
    }

    file.close();
    delete s;
}

