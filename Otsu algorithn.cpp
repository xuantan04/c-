#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// H�m t�nh to�n ngu?ng Otsu cho ?nh x�m
int otsu_threshold(vector<vector<int> > image) {
    int n = image.size();
    int m = image[0].size();

    // T�nh histogram c?a ?nh
    vector<int> histogram(256, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            histogram[image[i][j]]++;
        }
    }

    // T�nh t?ng s? di?m ?nh
    int total = n * m;

    // T�nh t?ng tr?ng s? v� t?ng tr?ng s? trung b�nh
    int sum = 0;
    for (int i = 0; i < 256; i++) {
        sum += i * histogram[i];
    }
    int sumB = 0;
    int wB = 0;
    int wF = 0;

    // T�nh gi� tr? ngu?ng Otsu
    int threshold = 0;
    double maxVar = 0.0;
    for (int i = 0; i < 256; i++) {
        wB += histogram[i];
        if (wB == 0) continue;
        wF = total - wB;
        if (wF == 0) break;
        sumB += i * histogram[i];
        double mB = (double)sumB / wB;
        double mF = (double)(sum - sumB) / wF;
        double varBetween = (double)wB * wF * pow(mB - mF, 2);
        if (varBetween > maxVar) {
            maxVar = varBetween;
            threshold = i;
        }
    }
      return threshold;
}

int main() {
    int n;
    cin >> n;

    vector<vector<int> > image(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> image[i][j];
        }
    }

    int threshold = otsu_threshold(image);
    cout << "Otsu threshold = " << threshold << endl;

    return 0;
}

