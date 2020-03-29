//火车按照字典序输出


    void permutation(string begin, string end) {
        int endLength = end.size(), beginLength = begin.size();
        if (endLength == 1) {
            cout << begin << end << endl;
            return;
        }
        string newEnd;
        for (int i = 0; i < endLength; i++) {
            newEnd = end.substr(0, i) + end.substr(i + 1);
            permutation(begin + end[i], newEnd);
        }
    }
