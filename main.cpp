//#include "Intersection.h"
//#include "Tree.h"
#include "Tests.h"

int main() {
    srand(time(NULL));

//    t1(); t2();
//    t3(); t4();

//    test1("../data/test1.txt");

    std::vector<Point> a;
    Point p1(1, 1), p2(2, 2);

    a.push_back(p1);
    a.push_back(p2);
    std::cout << a[0] << a[1] << std::endl;
    std::swap(a[0], a[1]);
    std::cout << a[0] << a[1] << std::endl;

//    Segs* s = new Segs;
//    std::string fileDir = "../data/test1.txt";
    //    test1(s, fileDir);
    //    s->readFromFile("../data/Segments.txt");




//    Segment *seg1;
//    Segment *seg2;
//
//    s.printS();
//
//    Naive n(s);
//    std::cout << n.intersection_naive(seg1, seg2) << std::endl;
//    std::cout << *seg1 << "; " << *seg2 << std::endl;
//
//    Tree t;
    return 0;
}
