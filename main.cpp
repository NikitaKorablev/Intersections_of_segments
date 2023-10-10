#include "Section.h"

int main() {
    S s;
    s.readFromFile("../data/Points.txt");

//    Segment *seg1;
//    Segment *seg2;

    s.printS();
    std::cout << s.intersection_naive() << std::endl;
//    std::cout << seg1 << "; " << seg2 << std::endl;

    return 0;
}
