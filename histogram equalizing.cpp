#include<iostream>
#include<vector>
using namespace std;
vector<int>compute_histogram(vector<vector<int> >&image,int num_levels){
    vector<int>histogram(num_levels,0);
    for(int i=0;i<image.size();i++){
        for(int j =0;j<image[i].size();j++){
            histogram[image[i][j]]++;
        }
    }
    return histogram;
}
vector<vector<int> >equalize_histogram(vector<vector<int> >&image,int num_levels){
    vector<vector<int> >equalized_image(image.size(),vector<int>(image[0].size(),0));
    vector<int> histogram=compute_histogram(image,num_levels);
    vector<int> cumulative_histogram(num_levels,0);
    int total_pixels=image.size()*image[0].size();
    cumulative_histogram[0]=histogram[0];
    for(int i=0;i<num_levels;i++){
        cumulative_histogram[i]=cumulative_histogram[i-1]+histogram[i];
    }
    for(int i=0;i<image.size();i++){
        for(int j =0;j<image[i].size();j++){
            int old_level=image[i][j];
            int new_level=(cumulative_histogram[old_level]+1)*(num_levels-1)/(total_pixels-1);
            equalized_image[i][j]=new_level;
        }
    }
    return equalized_image;
}
int main(){
    int m,n,num_levels;
    cin>>m>>n;
    cin>>num_levels;
    vector<vector<int> >image(m,vector<int>(n,0));
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            cin>>image[i][j];
        }
    }
    vector<vector<int> >result=equalize_histogram(image,num_levels);
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
           cout<<result[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}
