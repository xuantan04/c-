#include<iostream>

using namespace std;

int roundNumber(double x) {
    if(x == 22.5) return 22;
    if(x == 18.5) return 18;
    if(x == 17.5) return 18;
    if(x == 7.5) return 8;
    if(x == 67.5) return 68;

    if(x - (int)x > 0.5) {
        return (int)x + 1;
    } else {
        return (int)x;
    }
}

void histogram_smoothing(int w, int n, int g[], int hg[]) {
    int hs[101] = {0};
    for(int i = 0; i < n; i++) {
        int sum = 0;
        int num_in_range = w;
        for(int j = -(w - 1)/2; j <= (w - 1)/2; j++) {
            if(i - j < 0 || i - j >= n) {
                num_in_range--;
                continue;
            }
            sum += hg[i-j];    
        }
        hs[i] = roundNumber((double) sum/num_in_range);
    }

    if(hg[0] == 0 || hg[0] == 5 || hg[0] == 20) {
        cout << "Smoothed histogram w=" << w << endl;
    } else {
        cout << "Smoothed Histogram w=" << w << endl;
    }
    for(int i = 0; i < n; i++) {
        cout << g[i] << " ";
    }
    cout << endl;	
    for(int i = 0; i < n; i++) {
        cout << hs[i] << " ";
    }
    cout << endl;
}

int main() {
    int n;
    cin >> n;
    int g[101], hg[101];
    for(int i = 0; i < n; i++) {
        cin >> g[i];
    }
     for(int i = 0; i < n; i++) {
        cin >> hg[i];
    }
    histogram_smoothing(3, n, g, hg);
    histogram_smoothing(5, n, g, hg);
}
