#include <iostream>
#include <vector>
#include <utility>

// the class Solution has four principal attributes
// Sum: represents the total sum of the subvector
// MaxSum: represents a sum of a elements group that maximize that sum
// Suffix: represents a elements group that contains the vector last element and maximize the suffix sum
// Prefix: represents a elements group that contains the vector first element and maximize the prefix sum
class Solution {
    public:
        Solution();
        void updateInterval(int intervalId, int start, int end);
        float sum;
        float maxSubarraySum;
        float suffix;
        float prefix;
        std::pair<int, int> sumInterval;
        std::pair<int, int> maxSubarrayInterval;
        std::pair<int, int> suffixInterval;
        std::pair<int, int> prefixInterval;
};

std::vector<float> createTotalRatingVector(int numRows, int numCols);
void readFile();
