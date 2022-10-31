#include "rock.hpp"
#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>

std::vector<std::vector<float>> createRatingMatrix(int numRows, int numCols) {
    std::vector<std::vector<float>> matrix(numRows, std::vector<float>(numCols));
    std::string rating;
    float ratingFloat;
    
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++){
            std::cin >> rating;
            ratingFloat = std::stof(rating);
            std::cout << ratingFloat << " ";
            matrix[i][j] = 0;
        }
    }

    return matrix;
}


void readFile() {
    int numFriends = 0;
    int numShows = 0;

    std::cin >> numFriends;
    std::cin >> numShows;

    // while (numFriends != 0 && numShows != 0) {
        std::cout << numFriends << " ";
        std::cout << numShows << std::endl;

        std::vector<std::vector<float>> friendsRating = createRatingMatrix(numFriends, numShows);
    

        for (int i = 0; i < numFriends; i++) {
            for (int j = 0; j < numShows; j++) {
                std::cout << friendsRating[i][j] << " ";
            }
            std::cout << std::endl;
        }


    // }
}