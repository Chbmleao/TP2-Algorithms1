#include "rock.hpp"
#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <utility>

#define SUMSUBARRAY 0
#define MAXSUBARRAY 1
#define PRESUBARRAY 2
#define SUFSUBARRAY 3

Solution::Solution() {
    this->maxSubarraySum = 0;
    this->prefix = 0;
    this->suffix = 0;
    this->sum = 0;

    // initializes all intervals with -1 values, which means that the interval is empty
    this->sumInterval.first = -1;
    this->sumInterval.second = -1;
    this->maxSubarrayInterval.first = -1;
    this->maxSubarrayInterval.second = -1;
    this->suffixInterval.first = -1;
    this->suffixInterval.second = -1;
    this->prefixInterval.first = -1;
    this->prefixInterval.second = -1;
}

// receives an intervalId, a start index, and end index that must be the new interval
// updates one soltion interval
void Solution::updateInterval(int intervalId, int start, int end) {
    // if the start index or end index have invalid attributes, the function dont update the interval
    if(start == -1 || end == -1) 
        return;
    if (intervalId == SUMSUBARRAY) {
        this->sumInterval.first = start;
        this->sumInterval.second = end;
    }
    else if (intervalId == MAXSUBARRAY) {
        this->maxSubarrayInterval.first = start;
        this->maxSubarrayInterval.second = end;
    }
    else if (intervalId == PRESUBARRAY) {
        this->prefixInterval.first = start;
        this->prefixInterval.second = end;
    }
    else if (intervalId == SUFSUBARRAY) {
        this->suffixInterval.first = start;
        this->suffixInterval.second = end;
    }
}

// receives a float x and a float y
// returns the greater
float maxFloat(float x, float y) {
    if (x > y) 
        return x;
    return y; 
}

// receives a vector, the start index and end index
// returns the vector solution, with the Sum, MaxSum, Suffix and Prefix
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

    // divides the vector in the middle and determines a solution for each part
    Solution leftSolution = maxSubarraySum(vector, start, (start + end) / 2);
    Solution rightSolution = maxSubarraySum(vector, ((start+end) / 2)+1, end);

    solution.sum = leftSolution.sum + rightSolution.sum;
    solution.maxSubarraySum = maxFloat(maxFloat(leftSolution.maxSubarraySum, rightSolution.maxSubarraySum),
                                        leftSolution.suffix + rightSolution.prefix);
    solution.suffix = maxFloat(rightSolution.suffix, rightSolution.sum + leftSolution.suffix);
    solution.prefix = maxFloat(leftSolution.prefix, leftSolution.sum + rightSolution.prefix);

    // find the sum interval
    solution.updateInterval(SUMSUBARRAY, leftSolution.sumInterval.first, rightSolution.sumInterval.second);

    // find the max subarray interval
    if(solution.maxSubarraySum == leftSolution.maxSubarraySum)
        solution.updateInterval(MAXSUBARRAY, leftSolution.maxSubarrayInterval.first, leftSolution.maxSubarrayInterval.second);
    if(solution.maxSubarraySum == rightSolution.maxSubarraySum)
        solution.updateInterval(MAXSUBARRAY, rightSolution.maxSubarrayInterval.first, rightSolution.maxSubarrayInterval.second);
    if(solution.maxSubarraySum == (leftSolution.suffix + rightSolution.prefix))
        solution.updateInterval(MAXSUBARRAY, leftSolution.suffixInterval.first, rightSolution.prefixInterval.second);

    // find the suffix interval
    if(solution.suffix == rightSolution.suffix)
        solution.updateInterval(SUFSUBARRAY, rightSolution.suffixInterval.first, rightSolution.suffixInterval.second);
    if(solution.suffix == (leftSolution.suffix + rightSolution.sum))
        solution.updateInterval(SUFSUBARRAY, leftSolution.suffixInterval.first, rightSolution.sumInterval.second);

    // find the prefix interval
    if(solution.prefix == leftSolution.prefix)
        solution.updateInterval(PRESUBARRAY, leftSolution.prefixInterval.first, leftSolution.prefixInterval.second);
    if(solution.prefix == (leftSolution.sum + rightSolution.prefix))
        solution.updateInterval(PRESUBARRAY, leftSolution.sumInterval.first, rightSolution.prefixInterval.second);

    return solution;
}

// receives the num of rows and the num of cols to build the general score vector
// returns the general score vector, with each show score added
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

// main function
void readFile() {
    int numFriends = 0;
    int numShows = 0;

    std::cin >> numFriends;
    std::cin >> numShows;

    while (numFriends != 0 && numShows != 0) {
        std::vector<float> friendsRating = createTotalRatingVector(numFriends, numShows);

        Solution rockSolution = maxSubarraySum(friendsRating, 0, numShows-1);

        // iterates the vector to find the maximum value, if the vector only has negative elements
        if(rockSolution.maxSubarrayInterval.first == -1 && rockSolution.maxSubarrayInterval.second == -1) {
            int greaterShowIndex = 0; 
            int greaterShowRank = friendsRating[0];
            for (int i = 1; i < numShows; i++) {
                if (friendsRating[i] > greaterShowRank) {
                    greaterShowIndex = i;
                    greaterShowRank = friendsRating[i];
                }
            }
            
            // prints the interval that only contains the greater negative element
            std::cout << greaterShowIndex+1 << " " << greaterShowIndex+1 << std::endl;
        } else // prints the normal interval
            std::cout << rockSolution.maxSubarrayInterval.first + 1 << " " << rockSolution.maxSubarrayInterval.second + 1 << std::endl;    

        std::cin >> numFriends;
        std::cin >> numShows;
    }
}