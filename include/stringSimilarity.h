#ifndef STR_SIMILARITY
#define STR_SIMILARITY

#include <string>
#include <limits>

int levenshteinDistance(std::string a, std::string b);
int levenshteinDistanceHelper(std::string a, int endA, std::string b, int endB, int changes);
int findMax(int a, int b, int c);

bool isSubstring(std::string a, std::string b);
int autoSuggestScore(std::string a, std::string b);

#endif