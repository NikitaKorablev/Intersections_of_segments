//
// Created by nikita on 10/27/23.
//

#include "Tests.h"

/// Первый тест:
///     Задание отрезков по правилу:
///     n = 1, ..., 10^4 + 1 с шагом 100
/// \param s - указатель на место хранение отрезков
/// \param fileDir - в какой файл сохранять созданные отрезки (если нужно)
void test1(Segs* s, std::string fileDir) {
    s->clear();

    int n = 100001;
    for (int i = 1; i <= n; i+=100) {
        createRSegsByPoints(s, i);
        // TODO: замер времени
        // TODO: сохранение времени работы алгоритма в файл
        s->clear();
    }
}

/// Второй тест:
///     Задание отрезков по правилу:
///     n = 10^4 + 3, k = 1,..., 10^4 + 1 с шагом 100
/// \param s - указатель на место хранение отрезков
/// \param fileDir - в какой файл сохранять созданные отрезки (если нужно)
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

