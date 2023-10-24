//
// Created by nikita on 10/11/23.
//

#include "Intersection.h"

bool Naive::intersection_naive(Segment *&seg1, Segment *&seg2)  {
    bool res = false;
    int len = segments.getLen();
    for (int i = 0; i < len-1; i++) {
        for (int j = i + 1; j < len; j++) {
            if (intersection(segments[i], segments[j])) {
                res = true;

                seg1 = new Segment(segments[i]);
                seg2 = new Segment(segments[j]);

                break;
            }
        }
        if (res) break;
    }
    return res;
}



