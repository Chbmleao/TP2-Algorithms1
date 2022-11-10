#include <iostream>
#include <vector>
#include <utility>

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
