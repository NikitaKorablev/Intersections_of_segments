//#include "Intersection.h"
//#include "Tree.h"
#include "Tests.h"

int main() {
    srand(time(NULL));

    Segs s;

    Point p1(2, 1);
    Point p2(3, 4);
    Point p3(1, 0);
    Point p4(7, 9);

    p1.segmentIndex = s.getLen();
    p2.segmentIndex = s.getLen();
    Segment seg1(p1, p2);
    s.pushBack(seg1);

    p3.segmentIndex = s.getLen();
    p4.segmentIndex = s.getLen();
    Segment seg2(p3, p4);
    s.pushBack(seg2);

    s.sortPoints(0, s.getPointLen()-1);

    std:: cout << s.intersection_naive() << std::endl;
    std:: cout << s.intersection_effective() << std::endl;

//    test1();
//    test2();
//    test3();
//    test4();
    return 0;
}
