//
// Created by nikita on 10/27/23.
//

#include "Tests.h"

void test1() {
    Segs s;

    std::ofstream file1;
    file1.open("../dataTime/time1.txt");

    for (int i = 1; i <= 10001; i+=100) {
        std::cout << "i = "<< i << std::endl;
        s.rSetByPoints(i);

        auto start_time = std::chrono::high_resolution_clock::now();
        std::cout << s.intersection_naive() << std::endl;
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

        file1 << s.getLen() << " " << duration.count();

        start_time = std::chrono::high_resolution_clock::now();
        s.sortPoints(0, s.getPointLen() - 1);
        end_time = std::chrono::high_resolution_clock::now();
        auto sortDuration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);


        start_time = std::chrono::high_resolution_clock::now();
        if(!s.intersection_effective() && i != 1) throw -1;
        end_time = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

        file1 << " " << sortDuration.count() << " " << duration.count() << std::endl;

        s.clear();
    }
}

void test2(Segs* s, std::string fileDir) {
    s->clear();

    for (int i = 1; i <= 10001; i+=100) {
//        createRSegsByPoints(s, 10003, i);
        // TODO: замер времени
        // TODO: сохранение времени работы алгоритма в файл
        s->clear();
    }
}


void test3(Segs* s) {}
void test4(Segs* s) {}

