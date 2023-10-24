//
// Created by nikita on 10/11/23.
//

#include "Segments.h"

#ifndef INTERSECTIONS_OF_SEGMENTS_INTERSECTION_H
#define INTERSECTIONS_OF_SEGMENTS_INTERSECTION_H

class Naive {
    Segs segments;
public:
    Naive(const Segs& _segments) : segments(_segments) {};

    bool intersection_naive(Segment* &seg1, Segment* &seg2);
};

class Effective {
    Segs segments;
public:
    Effective(const Segs& _segments) : segments(_segments) {};
};
#endif //INTERSECTIONS_OF_SEGMENTS_INTERSECTION_H
