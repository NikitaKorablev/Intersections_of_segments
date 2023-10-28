//
// Created by nikita on 10/16/23.
//


#include "time.h"
#include "stdlib.h"
#include "cmath"
#include <unistd.h>
#include "random"
#include <functional>
#include "Segments.h"

#ifndef INTERSECTIONS_OF_SEGMENTS_RANDOMSEGMENTS_H
#define INTERSECTIONS_OF_SEGMENTS_RANDOMSEGMENTS_H

int r(int left = -1000, int right = 1000);

/// Функция создаёт случайный отрезок
/// \return возвращает случайно созданный отрезок длинной 1
Segment* randCreateSeg(int left = -100, int right = 100,
                       int down = -100, int up = 100);

/// Функция создаёт случайный отрезок
/// \param len - длинна создаваемого отрезка отрезка
/// \return Segment длинны len
Segment* randSegsByLength(double len);

/// Функция создаёт множество случайных отрезков.
/// Из них k не пересекаются, k+1 и k+2 пересекаются,
/// а остальные в произвольном порядке
/// \param s - мн-во для хранения созданных отрезков
/// \param n - кол-во отрезков в мн-ве
/// \param k - кол-во не пересекающихся отрезков
void createRSegsByPoints(Segs* &segments, int n, int k = -1);

/// Функция создаёт множество случайных отрезков,
/// по центральной точке отрезка, углу наклона относительно
/// оси обсцисс и длинне этого отрезка
/// \param segments - мн-во случайно заданных отрезков
/// \param length - длинна отрезков
/// \param n - кол-во отрезков
void createRSegsByLength(Segs* &segments, double length, int n);

void t1();
void t2();
void t3();
void t4();


#endif //INTERSECTIONS_OF_SEGMENTS_RANDOMSEGMENTS_H
