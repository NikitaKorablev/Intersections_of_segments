bool intersectionEffective() {
    Tree L; bool inter = false;
    segments->sortPoints(0, n-1);
    for (auto p : points) {
        Segment s = segments[p.segmentIndex];
        if (p.isLeft) {
            L.insert(L.getRoot(), s);                                   // O(log n)
            Node* addedSegment = L.search(s);                           // O(log n)
            Segment s1 = L.getPrev(addedSegment);                       // O(const)
            inter = intersection(s, s1);                                // O(const)
            if (inter) {
                std::cout << s << std::endl;
                std::cout << s1 << std::endl;
                break;
            }
            Segment s2 = L.getNext(addedSegment);                       // O(const)
            inter = intersection(s, s2);                                // O(const)
            if (inter) {
                std::cout << s << std::endl;
                std::cout << s2 << std::endl;
                break;
            }
        } else {
            Node* node = L.search(s);                                   // O(log n)
            Segment s1 = L.getPrev(node);                               // O(const)
            Segment s2 = L.getNext(node);                               // O(const)
            inter = intersection(s1, s2);                               // O(const)
            if (inter) {
                std::cout << s1 << std::endl;
                std::cout << s2 << std::endl;
                break;
            }
            L.remove(s);                                                // O(log n)
        }
    }
    return inter;
}