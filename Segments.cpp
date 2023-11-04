
// Created by nikita on 10/8/23.
//
#include "Segments.h"



//-----------------Segs-class-----------------

Segs::Segs(const Segs& s) {
    segments = s.segments;
}

Segment* Segs::randCreateSeg(int left, int right, int down, int up) {
//    std::cout << "call" << std::endl;
    double x1 = (double)rand() / RAND_MAX;
    double x2 = (double)rand() / RAND_MAX;
    double y1 = (double)rand() / RAND_MAX;
    double y2 = (double)rand() / RAND_MAX;

    while (x2 == x1) x2 = (double)rand() / RAND_MAX;

    Point p1(x1, y1), p2(x2, y2);
    p1.segmentIndex = getLen();
    p2.segmentIndex = getLen();

    return new Segment(p1, p2);
}

Segment* Segs::randSegsByLength(double len) {
    int angle = r(-90, 90);
    while (angle == 90) angle = r(-90, 90);
    angle *= M_PI / 180;

    double middleX = (double)rand() / RAND_MAX,
           middleY = (double)rand() / RAND_MAX;

    double x1 = middleX - len*std::cos(angle) / 2.0;
    double x2 = middleX + len*std::cos(angle) / 2.0;
    double y1 = middleY - len*std::sin(angle) / 2.0;
    double y2 = middleY + len*std::sin(angle) / 2.0;

    Point p1(x1, y1), p2(x2, y2);
    p1.segmentIndex = getLen();
    p2.segmentIndex = getLen();

    return new Segment(p1, p2);
}

void Segs::rSetByPoints(int n, int k) {
    clear();
    if (n == 0) return;

    if (n == 1) {
        pushBack(*randCreateSeg());
        return;
    }
    if (n < 0 || k < -1 || k >= n-1) throw -1;

    if (k == -1) k = n - 2;
    int i;
    for (i = 0; i < k + 1; ++i) {
        Segment* seg = randCreateSeg();
        bool isInter = false;

        // проверка на отсутствие пересечений
        for (const auto & segment : segments) {
            if (*seg == segment || intersection(*seg, segment)) {
                isInter = true;
                break;
            }
        }

        if (isInter) i--;
        else pushBack(*seg);
        delete seg;
    }

    Segment* seg = randCreateSeg();
    while (*seg == segments.back() || !intersection(*seg, segments.back())) {
        delete seg;
        seg = randCreateSeg();
    }
    pushBack(*seg); i++;
    delete seg;

    while (i < n-1) {
        pushBack(*randCreateSeg());
        i++;
    }
}

void Segs::rSetByLength(double length, int n) {
    clear();
    Segment* seg;
    for (int i = 0; i < n; i++) {
        seg = randSegsByLength(length);
        pushBack(*seg);
        delete seg;
    }
}

void Segs::pushBack(const Segment& seg) {
    segments.push_back(seg);
    points.push_back(seg.getP1());
    points.push_back(seg.getP2());
}

bool intersection(const Segment& a, const Segment& b) {
    Point aP1 = a.getP1(); Point bP1 = b.getP1();
    Point aP2 = a.getP2(); Point bP2 = b.getP2();
    Vector vec1(aP2 - aP1), vec2(bP2 - bP1);

    Vector v1(bP1 - aP1), v2(bP2 - aP1);
    Vector prod1(vec1 * v1), prod2(vec1 * v2);

    if (prod1.z() > 0 && prod2.z() > 0 ||
        prod1.z() < 0 && prod2.z() < 0) return false;

    Vector v3(aP1 - bP1), v4(aP2 - bP1);
    prod1 = vec2 * v3; prod2 = vec2 * v4;

    if (prod1.z() > 0 && prod2.z() > 0 ||
        prod1.z() < 0 && prod2.z() < 0) return false;

    return true;
}

int Segs::partition(int left, int right) {
    Point pivot = points[right];
    int wall = left;
    for (int i = left; i <= right-1; i++) {
        if (points[i] <= pivot) {
            std::swap(points[i], points[wall]);
            wall++;
        }
    }
    std::swap(points[wall], points[right]);
    return wall;
}

void Segs::sortPoints(int left, int right) {
//    if (right - left == 1) return;
    if (left < right) {
        int current = partition(left, right);
        sortPoints(left, current-1);
        sortPoints(current+1, right);
    }
}

void Segs::readFromFile(const std::string &filePath) {
    std::ifstream file;
    file.open(filePath);
    std::string res;
    if (file.is_open()) {
        while(getline(file, res)) {
            std::vector<float> coordinates;
            std::string element;
            std::stringstream elemInLine(res);
            while (getline(elemInLine, element, ' ')) {
                coordinates.push_back(stof(element));
            }

            Segment seg(Point(coordinates[0], coordinates[1]),
                        Point(coordinates[2], coordinates[3]));

            segments.push_back(seg);
        }
        file.close();
    }
}

void Segs::saveToFile(const std::string& filePath, bool clearFile) {
    if (filePath == "") throw -1;

    std::ofstream file;
    if (clearFile) file.open(filePath);
    else file.open(filePath, std::ios::app);

    if (file.is_open()) {
        for (auto &element: segments) {
            file << element << std::endl;
        }
        file << "~==~" << std::endl;
        file.close();
    } else {
        std::exit(-1);
    }
}

void Segs::printS() {
    for (auto &element: segments) {
        std::cout << element << std::endl;
        std::cout << "----------------" << std::endl;
    }
}

void Segs::clear() {
    segments.clear();
    points.clear();
}

bool Segs::intersection_naive() {
    bool res = false;
    for (int i = 0; i < getLen()-1; i++) {
//        std::cout << i << std::endl;
        for (int j = i + 1; j < getLen(); j++) {
//            std::cout << j << std::endl;
            if (intersection(segments[i], segments[j])) {
                std::cout << segments[i] << std::endl;
                std::cout << segments[j] << std::endl;
                res = true;
                break;
            }
        }
        if (res) break;
    }

    return res;
}

bool Segs::intersection_effective() {
    Tree tree;
    bool inter = false;

    int count = 0;
    for (auto p : points) {
        count++;
        Segment s = segments[p.segmentIndex];
        if (s.getP1().x == s.getP2().x) throw -1;
        if (p.isLeft) {
            Node* addedSegment = tree.insert(tree.getRoot(), s);
            Segment s1 = tree.getPrev(addedSegment);
            inter = intersection(s, s1);
            if (inter) {
                std::cout << "count = " << count << std::endl;
                break;
            }

            Segment s2 = tree.getNext(addedSegment);
            inter = intersection(s, s2);
            if (inter) {
                std::cout << "count = " << count << std::endl;
                break;
            }
        } else {
            Node* node = tree.search(tree.getRoot(), s, p.x);
            if (node == nullptr) throw -1;
            Segment s1 = tree.getPrev(node);
            Segment s2 = tree.getNext(node);
            inter = intersection(s1, s2);
            if (inter) {
                std::cout << "count = " << count << std::endl;
                break;
            }
            tree.remove(s);
            if (tree.search(tree.getRoot(), s, p.x)) throw -1;
        }
    }
//    std::cout << "count " << count << std::endl;
    return inter;
}

std::ostream& operator << (std::ostream& out, const std::vector<Point>& vec) {
    for(const auto & point : vec) {
        out << point << std::endl;
    }
    return out;
}