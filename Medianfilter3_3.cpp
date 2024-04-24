#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int median(vector<int>&arr){
    sort(arr.begin(),arr.end());
    return arr[4];
}
int main(){
    int n;
    cin>>n;
    vector<vector<int> >image(n,vector<int>(n));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>image[i][j];
        }
    }
    vector<vector<int> >filtered_image(n-2,vector<int>(n-2));
    for(int i=1;i<n-1;i++){
        for(int j=1;j<n-1;j++){
            vector<int>neighbors;
            for(int di=-1;di<=1;di++){
                for(int dj=-1;dj<=1;dj++){
                    neighbors.push_back(image[i+di][j+dj]);
                }
            }
            filtered_image[i-1][j-1]=median(neighbors);
        }
    }
    for(int i=0;i<n-2;i++){
        for(int j=0;j<n-2;j++){
            cout<<filtered_image[i][j]<<" ";
        }
        cout<<endl;
    }
}
