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

  int Gx[2][2] = {{-1, 0}, {0, 1}};
  int Gy[2][2] = {{0, -1}, {1, 0}};

  vector<vector<int> > gradient(size, vector<int>(size, 0));

  for (int i = 1; i < size - 1; i++) {
    for (int j = 1; j < size - 1; j++) {
      int gradient_x = 0;
      int gradient_y = 0;
      for (int k = 0; k < 2; k++) {
        for (int l = 0; l < 2; l++) {
          gradient_x += Gx[k][l] * image[i - k][j - l];
          gradient_y += Gy[k][l] * image[i - k][j - l];
        }
      }
      gradient[i][j] = sqrt(gradient_x * gradient_x + gradient_y * gradient_y);
    }
  }

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      cout << int(gradient[i][j]) << " ";
    }
    cout << "\n";
  }

  return 0;
}
