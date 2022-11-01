#include <iostream>
#include <vector>

class Solution {
    public:
        Solution();
        void updateInterval(int intervalId, int start, int end);
        float sum;
        float maxSubarraySum;
        float suffix;
        float prefix;
        int sumInterval[2];
        int maxSubarrayInterval[2];
        int suffixInterval[2];
        int prefixInterval[2];
};

std::vector<float> createTotalRatingVector(int numRows, int numCols);
void readFile();
