//
// Created by nikita on 10/27/23.
//

#include "Tests.h"

void test1(std::string fileDir) {
    Segs s;

    std::ofstream file1;
    file1.open("../dataTime/time1.txt");

    std::ifstream file;
    file.open(fileDir);

    std::string res;
    if (file1.is_open()) {
        int count = 0;
        while(getline(file, res)) {
            if (res == "~==~") {
                auto start_time = std::chrono::high_resolution_clock::now();
                s.intersection_naive();
                auto end_time = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

                file1 << count << " " << duration.count();

                start_time = std::chrono::high_resolution_clock::now();
                s.intersection_effective();
                end_time = std::chrono::high_resolution_clock::now();
                duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

                file1 << " " << duration.count() << std::endl;

                count = 0;
            } else {
                std::vector<int> coordinates;
                std::string element;
                std::stringstream elemInLine(res);
                while (getline(elemInLine, element, ' ')) {
                    coordinates.push_back(stoi(element));
                }

                Point p1(coordinates[0], coordinates[1]);
                Point p2(coordinates[2], coordinates[3]);

                p1.segmentIndex = s.getLen();
                p2.segmentIndex = s.getLen();

                Segment seg(p1, p2);
                s.pushBack(seg); count++;
                s.pushBackPoint(p1); s.pushBackPoint(p2);
            }
        }
        file1.close();
    }
}

void test2(Segs* s, std::string fileDir) {
    s->clear();

    for (int i = 1; i <= 10001; i+=100) {
        createRSegsByPoints(s, 10003, i);
        // TODO: замер времени
        // TODO: сохранение времени работы алгоритма в файл
        s->clear();
    }
}


void test3(Segs* s) {}
void test4(Segs* s) {}

