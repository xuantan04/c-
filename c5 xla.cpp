#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric> 

int calculateIsodataThreshold(int n, std::vector<std::vector<int > >& image) {
    // Initialize the threshold value with an arbitrary initial guess.
    int threshold = 128;
    
    // Create a vector to store pixel values greater and less than the threshold.
    std::vector<int> greaterValues;
    std::vector<int> lessValues;
    
    while (true) {
        greaterValues.clear();
        lessValues.clear();
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (image[i][j] > threshold) {
                    greaterValues.push_back(image[i][j]);
                } else {
                    lessValues.push_back(image[i][j]);
                }
            }
        }
        
        // Calculate the new threshold value as the average of the two groups.
        int newThreshold = (std::accumulate(greaterValues.begin(), greaterValues.end(), 0) / greaterValues.size() +
                            std::accumulate(lessValues.begin(), lessValues.end(), 0) / lessValues.size()) / 2;
        
        // Check for convergence.
        if (newThreshold == threshold) {
            break;
        }
        
        threshold = newThreshold;
    }
    
    return threshold;
}

int main() {
    int caseNum;
    std::cin >> caseNum;
    
    int n;
    std::cin >> n;
    
    std::vector<std::vector<int> > image(n, std::vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> image[i][j];
        }
    }
    
    if (caseNum == 1) {
        int threshold = calculateIsodataThreshold(n, image);
        std::cout << "Isodata threshold = " << threshold << std::endl;
    }
    
    return 0;
}

