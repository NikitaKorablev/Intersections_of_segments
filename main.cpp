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

    Segment seg1(p1, p2);
    s.pushBack(seg1);

    Segment seg2(p3, p4);
    s.pushBack(seg2);

    s.sortPoints(0, s.getPointLen()-1);

    std:: cout << s.intersectionNaive() << std::endl;
    std:: cout << s.intersectionEffective() << std::endl;

//    test1("../dataTime/time1.txt");
//    test2("../dataTime/time2.txt");
//    test3("../dataTime/time3.txt");
//    test4("../dataTime/time4.txt");
    return 0;
}
