#include <iostream>
#include <vector>

using namespace std;

// Hàm th?c hi?n k? thu?t error diffusion
vector<vector<int> > errorDiffusion(vector<vector<int> >& image, int threshold = 127) {
    int height = image.size();
    int width = image[0].size();
    vector<vector<int> > result(height, vector<int>(width, 0));

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int oldPixel = image[y][x];
            int newPixel = (oldPixel >= threshold) ? 255 : 0;
            result[y][x] = newPixel;
            int error = oldPixel - newPixel;

            if (x < width - 1) {
                image[y][x + 1] += error * 7 / 16;
            }
            if (y < height - 1) {
                if (x > 0) {
                    image[y + 1][x - 1] += error * 3 / 16;
                }
                image[y + 1][x] += error * 5 / 16;
                if (x < width - 1) {
                    image[y + 1][x + 1] += error * 1 / 16;
                }
            }
        }
    }

    return result;
}

int main() {
    int size;
    cin >> size;
    vector<vector<int> > image(size, vector<int>(size));

    // Nh?p ma tr?n giá tr? m?c xám c?a ?nh
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            cin >> image[y][x];
        }
    }

    int threshold = 127;
    vector<vector<int> > result = errorDiffusion(image, threshold);

    // In ra ma tr?n k?t qu?
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            cout << result[y][x] << " ";
        }
        cout << endl;
    }

    return 0;
}
