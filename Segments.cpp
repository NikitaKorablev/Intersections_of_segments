
// Created by nikita on 10/8/23.
//
#include "Segments.h"



//-----------------Segs-class-----------------

Segs::Segs(const Segs& s) {
    segments = s.segments;
}

Segment* Segs::randCreateSeg(int width) {
    double x1 = (double)rand() / RAND_MAX * width;
    double x2 = (double)rand() / RAND_MAX * width;
    double y1 = (double)rand() / RAND_MAX * width;
    double y2 = (double)rand() / RAND_MAX * width;

    while (x2 == x1) x2 = (double)rand() / RAND_MAX * width;

    Point p1(x1, y1), p2(x2, y2);
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
    return new Segment(p1, p2);
}

void Segs::rSetByPoints(int n, int k, int width) {
    clear();
    if (n == 0) {
        pushBack(*randCreateSeg(width));
        return;
    }
    if (n < 0 || k < -1 || k >= n-1) throw -1;

    if (n == 1) return;

    if (k == -1) k = n - 2;

    Segment* seg;
    for (int i = 0; i < n; ++i) {
        seg = randCreateSeg(width);
        std::cout << "k: " << k << " i: " << i << std::endl;
        if (i == k+1) {
            while (!intersection(*seg, segments.back()) ||
                    seg_has_inter_wout_last(*seg, k)) {
//                std::cout <<" i: " << i << std::endl;
                delete seg;
                seg = randCreateSeg(width);
            }
        } else {
            while (seg_has_inter_befor_K(*seg, k)) {
//                std::cout << "k: " << k << std::endl;
                delete seg;
                seg = randCreateSeg(width);
            }
        }
        pushBack(*seg);
        delete seg;
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

void Segs::pushBack(Segment seg) {
    seg.setSegIndexForPoints(static_cast<int>(getLen()));

    segments.push_back(seg);
    points.push_back(seg.getP1());
    points.push_back(seg.getP2());
}

//void Segs::pushBack(Segment* seg) {
//    seg->setSegIndexForPoints(static_cast<int>(getLen()));
//
//    segments.push_back(*seg);
//    points.push_back(seg->getP1());
//    points.push_back(seg->getP2());
//}

//void Segs::changeLast(Segment seg) {
//    seg.setSegIndexForPoints(static_cast<int>(getLen()) - 1);
//
//    Segment old_seg = segments[static_cast<int>(getLen())-1];
//    points[find_point_ind(old_seg.getP1())] = seg.getP1();
//    points[find_point_ind(old_seg.getP2())] = seg.getP2();
//
//    segments[static_cast<int>(getLen())] = seg;
//
//    sortPoints(0, static_cast<int>(getPointLen()) - 1);
//}

//void Segs::changeLast(Segment* seg) {
//    segments.pop_back();
//    points.clear();
//
//    for (const auto& s: segments) {
//        points.push_back(s.getP1());
//        points.push_back(s.getP2());
//    }
//
//    pushBack(seg);
//    sortPoints(0, static_cast<int>(getPointLen()) - 1);
//}

bool intersection(const Segment& a, const Segment& b) {
//    if (a.getP1().segmentIndex == -1 || b.getP1().segmentIndex == -1)
//        return false;

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

bool Segs::intersectionNaive() {
    std::cout << "naive start" << std::endl;
    bool res = false;
    for (int i = 0; i < getLen()-1; i++) {
        for (int j = i + 1; j < getLen(); j++) {
            if (intersection(segments[i], segments[j])) {
                std::cout << i << " " << j << std::endl;
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

bool Segs::intersectionEffective() {
    Tree tree;
    bool inter = false;

    int count = 0;
    for (auto p : points) {
        count++;
        Segment s;
        s = segments[p.segmentIndex];

        if (s.getP1().x == s.getP2().x) throw -1;

        if (p.isLeft) {
            tree.insert(tree.getRoot(), s);
            Node* addedSegment = tree.search(tree.getRoot(), s, s.getP1().x);
            Segment s1 = tree.getPrev(addedSegment);
            inter = intersection(s, s1);
            if (s == s1) throw -1;
            if (inter) {
                std::cout << s << std::endl;
                std::cout << s1 << std::endl;
                break;
            }
            Segment s2 = tree.getNext(addedSegment);
            inter = intersection(s, s2);
            if (s == s2) throw -1;
            if (inter) {
                std::cout << s << std::endl;
                std::cout << s2 << std::endl;
                break;
            }
        } else {
            Node* node = tree.search(tree.getRoot(), s, p.x);
            if (!node) {
                node = tree.search(tree.getRoot(), s, p.x);
            }
            if (s != node->seg) throw -1;
            Segment s1 = tree.getPrev(node);
            Segment s2 = tree.getNext(node);
            inter = intersection(s1, s2);
            if (s1 == s2) throw -1;
            if (inter) {
                std::cout << s1 << std::endl;
                std::cout << s2 << std::endl;
                break;
            }
            tree.remove(s);
            Node* n = tree.search(tree.getRoot(), s, p.x);
            if (n) throw -1;
        }
    }
    std::cout << (count == points.size()) << std::endl;
    return inter;
}

bool Segs::seg_has_inter_befor_K(const Segment& s, int k) {
    bool isInter = false;
    for (int i = 0; i < k+2 && i < segments.size(); i++) {
        if (s == segments[i] || intersection(s, segments[i])) {
            isInter = true;
            continue;
        }
    }
    return isInter;
}

bool Segs::seg_has_inter_wout_last(const Segment& s, int k) {
    return seg_has_inter_befor_K(s, k-2);
}

std::ostream& operator << (std::ostream& out, const std::vector<Point>& vec) {
    for(const auto & point : vec) {
        out << point << std::endl;
    }
    return out;
}