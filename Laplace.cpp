#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int size;
  cin >> size;
  vector<vector<int> > image(size, vector<int>(size));
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      cin >> image[i][j];
    }
  }

  int Laplace[3][3] = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};

  vector<vector<int> > gradient(size, vector<int>(size, 0));

  for (int i = 1; i < size - 1; i++) {
    for (int j = 1; j < size - 1; j++) {
      int sum = 0;
      for (int k = -1; k <= 1; k++) {
        for (int l = -1; l <= 1; l++) {
          sum += Laplace[k + 1][l + 1] * image[i - k][j - l];
        }
      }
      gradient[i][j] = sum;
    }
  }

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      cout << abs(gradient[i][j]) << " ";
    }
    cout << "\n";
  }

  return 0;
}
