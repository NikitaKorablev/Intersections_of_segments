//
// Created by nikita on 10/11/23.
//

#ifndef INTERSECTIONS_OF_SEGMENTS_INTERSECTION_H
#define INTERSECTIONS_OF_SEGMENTS_INTERSECTION_H

#include "Segments.h"

class BaseInter {
protected:
    virtual bool intersection(Segment a, Segment b);
};

class Naive: BaseInter {
    Segs segments;
public:
    Naive(const Segs& _segments) : segments(_segments) {};

    bool intersection_naive(Segment* &seg1, Segment* &seg2);
};

class Effective: BaseInter {
    Segs segments;
public:
    Effective(const Segs& _segments) : segments(_segments) {};
};
#endif //INTERSECTIONS_OF_SEGMENTS_INTERSECTION_H
