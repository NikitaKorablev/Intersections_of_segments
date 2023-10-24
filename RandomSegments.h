//
// Created by nikita on 10/16/23.
//


#include "time.h"
#include "stdlib.h"
#include "cmath"
#include <unistd.h>

#ifndef INTERSECTIONS_OF_SEGMENTS_RANDOMSEGMENTS_H
#define INTERSECTIONS_OF_SEGMENTS_RANDOMSEGMENTS_H

#include "Segments.h"

double r(int left, int right, int time = 0);
void createRSegs(Segs* s, int k);

/// randCreateSeg()
/// \return возвращает случайно созданный отрезок длинной 1
Segment* randCreateSeg(int left = -100, int right = 100);

/// rSegmentsKShift()
/// \param s - указатель на множество сегментов
/// \param kMin - начальное значение не пересекающихся отрезков
/// \param kMax - конечкое значение не пересекающихся отрезков
/// \param shift - шаг по перебору не пересекающихся отрезков
void rSegmentsKShift(Segs* s, int kMin, int kMax, int shift = 1);

/// rSegmentsNShift()
/// \param s - указатель на множество сегментов
/// \param nMin - начальное значение пересекающихся отрезков
/// \param nMax - конечкое значение пересекающихся отрезков
/// \param shift - шаг по перебору пересекающихся отрезков
void rSegmentsNShift(Segs* s, int nMin, int nMax, int shift = 1);

#endif //INTERSECTIONS_OF_SEGMENTS_RANDOMSEGMENTS_H
