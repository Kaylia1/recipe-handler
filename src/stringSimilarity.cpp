#include "../include/stringSimilarity.h"

int levenshteinDistance(std::string a, std::string b) {
    // printf("passed in %s %s\n", a.c_str(), b.c_str());
    if(a.size() == 0) return b.size();
    if(b.size() == 0) return a.size();
    
    return levenshteinDistanceHelper(a, a.size() - 1, b, b.size() - 1, 0);
    // printf("ret is %d for %s %s\n", x, a.c_str(), b.c_str());
    // return x;
}

int levenshteinDistanceHelper(std::string a, int endA, std::string b, int endB, int changes) {
    // printf("a size is %d and b size is %d\n", endA, endB);

    //todo consider multithreading?
    if(changes >= 30) return std::numeric_limits<int>::max(); // too dissimilar to bother continue checking

    //if either string is empty, takes length of other string to convert
    if(endA < 0 && endB < 0) return changes;
    if(endB < 0) return changes + endA + 1;
    if(endA < 0) return changes + endB + 1;

    //start from end of string
    // printf("testing %c %c\n", a[endA], b[endB]);
    if(a[endA] == b[endB]){ //last characters match, move on without incrementing diff count
        return levenshteinDistanceHelper(a, endA - 1, b, endB - 1, changes);
    }

    int replace = levenshteinDistanceHelper(a, endA - 1, b, endB - 1, changes + 1);
    int removeA = levenshteinDistanceHelper(a, endA - 1, b, endB,     changes + 1);
    int removeB = levenshteinDistanceHelper(a, endA    , b, endB - 1, changes + 1);

    int curChanges = findMax(replace, removeA, removeB);// + 1;
    return curChanges;
}

int findMax(int a, int b, int c){ //actually min now
    if(a <= b && a <= c) return a;
    if(b <= c) return b;
    return c;
}