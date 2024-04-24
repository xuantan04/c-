#include <iostream>
#include <cmath>

using namespace std;

// Define the Gaussian filters
double gaussian_filter1[5][5] = {
    {1.0/159, 1.0/23, 1.0/66, 1.0/23, 1.0/159},
    {1.0/23, 1.0/33, 1.0/66, 1.0/33, 1.0/23},
    {1.0/66, 1.0/98, 1.0/66, 1.0/98, 1.0/66},
    {1.0/23, 1.0/33, 1.0/66, 1.0/33, 1.0/23},
    {1.0/159, 1.0/23, 1.0/66, 1.0/23, 1.0/159}
};

double gaussian_filter2[5][5] = {
    {1.0/463, 1.0/276, 1.0/125, 1.0/276, 1.0/463},
    {1.0/276, 1.0/164, 1.0/74, 1.0/164, 1.0/276},
    {1.0/125, 1.0/74, 1.0/33, 1.0/74, 1.0/125},
    {1.0/276, 1.0/164, 1.0/74, 1.0/164, 1.0/276},
    {1.0/463, 1.0/276, 1.0/125, 1.0/276, 1.0/463}
};

// Function to apply the filter to an image
void applyFilter(int image[100][100], double filter[5][5], int result[100][100], int size) {
    int filterSize = 5;
    int padding = 2;

    for (int i = padding; i < size - padding; i++) {
        for (int j = padding; j < size - padding; j++) {
            double sum = 0.0;
            for (int m = -padding; m <= padding; m++) {
                for (int n = -padding; n <= padding; n++) {
                    sum += image[i + m][j + n] * filter[m + padding][n + padding];
                }
            }
            result[i][j] = round(fabs(sum));
        }
    }
}

// Function to print a 2D array
void printMatrix(int matrix[100][100], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int caseNum, size;
    cin >> caseNum >> size;
    int image[100][100] = {0};

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cin >> image[i][j];
        }
    }

    int result[100][100] = {0};

    if (caseNum == 1) {
        applyFilter(image, gaussian_filter1, result, size);
        cout << "LOG" << endl;
        printMatrix(result, size);
    } else if (caseNum == 2) {
        int result1[100][100] = {0};
        int result2[100][100] = {0};
        applyFilter(image, gaussian_filter1, result1, size);
        applyFilter(image, gaussian_filter2, result2, size);

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                result[i][j] = abs(result1[i][j] - result2[i][j]);
            }
        }

        cout << "DOG" << endl;
        printMatrix(result, size);
    }

    return 0;
}
