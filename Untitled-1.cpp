#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Define the Gaussian filters
vector<vector<double>> gaussian_filter1 = {
    {1.0/159, 1.0/23, 1.0/66, 1.0/23, 1.0/159},
    {1.0/23, 1.0/33, 1.0/66, 1.0/33, 1.0/23},
    {1.0/66, 1.0/98, 1.0/66, 1.0/98, 1.0/66},
    {1.0/23, 1.0/33, 1.0/66, 1.0/33, 1.0/23},
    {1.0/159, 1.0/23, 1.0/66, 1.0/23, 1.0/159}
};

vector<vector<double>> gaussian_filter2 = {
    {1.0/463, 1.0/276, 1.0/125, 1.0/276, 1.0/463},
    {1.0/276, 1.0/164, 1.0/74, 1.0/164, 1.0/276},
    {1.0/125, 1.0/74, 1.0/33, 1.0/74, 1.0/125},
    {1.0/276, 1.0/164, 1.0/74, 1.0/164, 1.0/276},
    {1.0/463, 1.0/276, 1.0/125, 1.0/276, 1.0/463}
};

// Function to apply the filter to an image
vector<vector<int>> applyFilter(vector<vector<int>> &image, vector<vector<double>> &filter) {
    int height = image.size();
    int width = image[0].size();
    int filterSize = filter.size();
    int padding = filterSize / 2;
    vector<vector<int>> result(height, vector<int>(width, 0));

    for (int i = padding; i < height - padding; i++) {
        for (int j = padding; j < width - padding; j++) {
            double sum = 0.0;
            for (int m = -padding; m <= padding; m++) {
                for (int n = -padding; n <= padding; n++) {
                    sum += image[i + m][j + n] * filter[m + padding][n + padding];
                }
            }
            result[i][j] = round(fabs(sum));
        }
    }

    return result;
}

// Function to print a 2D vector
void printMatrix(vector<vector<int>> &matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int caseNum, size;
    cin >> caseNum >> size;
    vector<vector<int>> image(size, vector<int>(size, 0));

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cin >> image[i][j];
        }
    }

    if (caseNum == 1) {
        vector<vector<int>> result = applyFilter(image, gaussian_filter1);
        cout << "LOG" << endl;
        printMatrix(result);
    } else if (caseNum == 2) {
        vector<vector<int>> result1 = applyFilter(image, gaussian_filter1);
        vector<vector<int>> result2 = applyFilter(image, gaussian_filter2);
        vector<vector<int>> result(size, vector<int>(size, 0));

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                result[i][j] = abs(result1[i][j] - result2[i][j]);
            }
        }

        cout << "DOG" << endl;
        printMatrix(result);
    }

    return 0;
}