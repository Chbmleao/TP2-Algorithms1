#include "rock.hpp"
#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>

Solution::Solution() {
    this->maxSubarraySum = 0;
    this->prefix = 0;
    this->suffix = 0;
    this->sum = 0;
}

float maxFloat(float x, float y) {
    if (x >= y)
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

        return solution;
    }

    Solution leftSolution = maxSubarraySum(vector, start, (start + end) / 2);
    Solution rightSolution = maxSubarraySum(vector, ((start+end) / 2)+1, end);

    solution.sum = leftSolution.sum + rightSolution.sum;
    solution.maxSubarraySum = maxFloat(maxFloat(leftSolution.maxSubarraySum, rightSolution.maxSubarraySum),
                                        leftSolution.suffix + rightSolution.prefix);
    solution.suffix = maxFloat(rightSolution.suffix, rightSolution.sum + leftSolution.suffix);
    solution.prefix = maxFloat(leftSolution.prefix, leftSolution.sum + rightSolution.prefix);

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

        std::cout << "Max SubArray Sum: " << rockSolution.maxSubarraySum << std::endl << std::endl;

        std::cin >> numFriends;
        std::cin >> numShows;
    } ;

}