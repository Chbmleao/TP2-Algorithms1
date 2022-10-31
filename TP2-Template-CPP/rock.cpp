#include "rock.hpp"
#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>

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

    do {
        std::cin >> numFriends;
        std::cin >> numShows;

        std::vector<float> friendsRating = createTotalRatingVector(numFriends, numShows);
    

        for (int i = 0; i < numShows; i++) {
            std::cout << friendsRating[i] << " ";
        }
        std::cout << std::endl;

    } while (numFriends != 0 && numShows != 0);
}