//
// Created by nikita on 10/8/23.
//
#include "Section.h"

bool S::intersection(Segment a, Segment b) {
    Point aP1 = a.getP1(); Point bP1 = b.getP1();
    Point aP2 = a.getP2(); Point bP2 = b.getP2();
    if (a.getK() == b.getK() && a.getB() == b.getB()) {
        if (aP1.x <= bP1.x && bP1.x <= aP2.x || aP1.x <= bP2.x && bP2.x <= aP2.x) return true;
        else return false;
    } else if (a.getK() == b.getK()) {
        return false;
    } else {
        double x = (b.getB() - a.getB()) / (a.getK() - b.getK());
        if (!(aP1.x <= x && x <= aP2.x) || !(bP1.x <= x && x <= bP2.x)) return false;
        else return true;
    }
}

void S::appendSection(Segment sec)  {
    s.push_back(sec);
    len++;
}

bool S::intersection_naive(Segment *seg1, Segment *seg2)  {
    bool res = false;
    for (int i = 0; i < len-1; i++) {
        for (int j = i + 1; j < len; j++) {
            if (intersection(s[i], s[j])) {
                res = true;
                if (seg1 && seg2) {
                    *seg1 = s[i];
                }
                break;
            }
        }
        if (res) break;
    }
    return res;
}

void S::readFromFile(const std::string &filePath) {
    std::ifstream file;
    file.open(filePath);
    std::string res;
    if (file.is_open()) {
        while(getline(file, res)) {
            std::cout << res << std::endl;

            std::vector<int> coordinates;
            std::string element;
            std::stringstream elemInLine(res);
            while (getline(elemInLine, element, ' ')) {
                coordinates.push_back(stoi(element));
            }
        }
    }
}