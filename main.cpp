#include "Intersection.h"
#include "Tree.h"

int main() {
    Segs s;
    s.readFromFile("../data/Points.txt");

    Segment *seg1;
    Segment *seg2;

    s.printS();

    Naive n(s);
    std::cout << n.intersection_naive(seg1, seg2) << std::endl;
    std::cout << *seg1 << "; " << *seg2 << std::endl;

    Tree t;

    return 0;
}
