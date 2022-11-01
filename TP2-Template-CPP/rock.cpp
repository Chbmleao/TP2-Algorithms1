#include "rock.hpp"
#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>

#define SUMSUBARRAY 0
#define MAXSUBARRAY 1
#define PRESUBARRAY 2
#define SUFSUBARRAY 3

Solution::Solution() {
    this->maxSubarraySum = 0;
    this->prefix = 0;
    this->suffix = 0;
    this->sum = 0;
    this->sumInterval[0] = -1;
    this->sumInterval[1] = -1;
    this->maxSubarrayInterval[0] = -1;
    this->maxSubarrayInterval[1] = -1;
    this->suffixInterval[0] = -1;
    this->suffixInterval[1] = -1;
    this->prefixInterval[0] = -1;
    this->prefixInterval[1] = -1;
}

void Solution::updateInterval(int intervalId, int start, int end) {
    if(start == -1 || end == -1)
        return;
    if (intervalId == SUMSUBARRAY) {
        this->sumInterval[0] = start;
        this->sumInterval[1] = end;
    }
    if (intervalId == MAXSUBARRAY) {
        this->maxSubarrayInterval[0] = start;
        this->maxSubarrayInterval[1] = end;
    }
    if (intervalId == PRESUBARRAY) {
        this->prefixInterval[0] = start;
        this->prefixInterval[1] = end;
    }
    if (intervalId == SUFSUBARRAY) {
        this->suffixInterval[0] = start;
        this->suffixInterval[1] = end;
    }
}

float maxFloat(float x, float y) {
    if (x > y)
        return x;
    return y;
}

Solution maxSubarraySum(std::vector<float> vector, int start, int end) {
    Solution solution = Solution();
    if (start == end) {
        solution.sum = vector[start];
        solution.maxSubarraySum = maxFloat(0, vector[start]);
        solution.suffix = maxFloat(0, vector[start]);
        solution.prefix = maxFloat(0, vector[start]);

        solution.updateInterval(SUMSUBARRAY, start, end);

        if(vector[start] >= 0) {
            solution.updateInterval(MAXSUBARRAY, start, end);
            solution.updateInterval(SUFSUBARRAY, start, end);
            solution.updateInterval(PRESUBARRAY, start, end);
        }
        

        return solution;
    }

    Solution leftSolution = maxSubarraySum(vector, start, (start + end) / 2);
    Solution rightSolution = maxSubarraySum(vector, ((start+end) / 2)+1, end);

    solution.sum = leftSolution.sum + rightSolution.sum;
    solution.maxSubarraySum = maxFloat(maxFloat(leftSolution.maxSubarraySum, rightSolution.maxSubarraySum),
                                        leftSolution.suffix + rightSolution.prefix);
    solution.suffix = maxFloat(rightSolution.suffix, rightSolution.sum + leftSolution.suffix);
    solution.prefix = maxFloat(leftSolution.prefix, leftSolution.sum + rightSolution.prefix);

    // find the sum interval
    solution.updateInterval(SUMSUBARRAY, leftSolution.sumInterval[0], rightSolution.sumInterval[1]);

    // find the max subarray interval
    if(solution.maxSubarraySum == leftSolution.maxSubarraySum)
        solution.updateInterval(MAXSUBARRAY, leftSolution.maxSubarrayInterval[0], leftSolution.maxSubarrayInterval[1]);
    if(solution.maxSubarraySum == rightSolution.maxSubarraySum)
        solution.updateInterval(MAXSUBARRAY, rightSolution.maxSubarrayInterval[0], rightSolution.maxSubarrayInterval[1]);
    if(solution.maxSubarraySum == (leftSolution.suffix + rightSolution.prefix))
        solution.updateInterval(MAXSUBARRAY, leftSolution.suffixInterval[0], rightSolution.prefixInterval[1]);

    // find the suffix interval
    if(solution.suffix == rightSolution.suffix)
        solution.updateInterval(SUFSUBARRAY, rightSolution.suffixInterval[0], rightSolution.suffixInterval[1]);
    if(solution.suffix == (leftSolution.suffix + rightSolution.sum))
        solution.updateInterval(SUFSUBARRAY, leftSolution.suffixInterval[0], rightSolution.sumInterval[1]);

    // find the prefix interval
    if(solution.prefix == leftSolution.prefix)
        solution.updateInterval(PRESUBARRAY, leftSolution.prefixInterval[0], leftSolution.prefixInterval[1]);
    if(solution.prefix == (leftSolution.sum + rightSolution.prefix))
        solution.updateInterval(PRESUBARRAY, leftSolution.sumInterval[0], rightSolution.prefixInterval[1]);

    return solution;
}

std::vector<float> createTotalRatingVector(int numRows, int numCols) {
    std::vector<float> totalRating(numCols);

    for (int i = 0; i < numCols; i++) {
        totalRating[i] = 0;
    }

    float rating = 0;
    
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++){
            std::cin >> rating;
            totalRating[j] += rating; 
        }
    }

    return totalRating;
}


void readFile() {
    int numFriends = 0;
    int numShows = 0;

    std::cin >> numFriends;
    std::cin >> numShows;

    while (numFriends != 0 && numShows != 0) {
        std::vector<float> friendsRating = createTotalRatingVector(numFriends, numShows);
    
        std::cout << "Vector: " << std::endl;
        for (int i = 0; i < numShows; i++) {
            std::cout << friendsRating[i] << " ";
        }
        std::cout << std::endl;

        Solution rockSolution = maxSubarraySum(friendsRating, 0, numShows-1);

        std::cout << "Max SubArray Sum: " << rockSolution.maxSubarraySum << std::endl;
        std::cout << "Max Interval: " << rockSolution.maxSubarrayInterval[0]+1 << " - " << rockSolution.maxSubarrayInterval[1]+1 << std::endl << std::endl;

        std::cin >> numFriends;
        std::cin >> numShows;
    }
}