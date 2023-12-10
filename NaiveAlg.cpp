bool intersectionNaive() {
    int n = S.size();
    bool res = false;
    for (int i = 0; i < n-1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (intersection(S[i], S[j])) {
                std::cout << S[i] << std::endl;
                std::cout << S[j] << std::endl;
                res = true;
                break;
            }
        }
        if (res) break;
    }

    return res;
}