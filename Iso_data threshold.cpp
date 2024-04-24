#include<iostream>
#include<math.h>
#define MAX 256
#define L 256
using namespace std;
int main(){
    int n, i, j, k, I[MAX][MAX];
    double  nk[MAX], pk[MAX], t0, t1, epsi, m1, m2, sum;
    cin>>n;
    for(i=0; i<=L-1; i++)   nk[i]=0;
    for(i=1; i<=n; i++)
        for(j=1; j<=n; j++){    cin>>I[i][j];   nk[I[i][j]]++;  }
    for(i=0; i<=L-1; i++)   pk[i]=nk[i]/(n*n);
    double sumipi=0, sumpi=0;
    for(i=0; i<=L-1; i++){  sumipi+=i*pk[i];    sumpi+=pk[i];   }
    t0=t1=sumipi/sumpi;
    do{
        t0=t1;
        sumipi=0; sumpi=0;
        for(i=0; i<=(int)t0; i++){  sumipi+=i*pk[i];    sumpi+=pk[i];   }
        if(sumpi!=0)
            m1=sumipi/sumpi;
        else
            m1=0;
        sumipi=0; sumpi=0;
        for(i=L-1; i>(int)t0; i--){  sumipi+=i*pk[i];    sumpi+=pk[i];   }
        if(sumpi!=0)
            m2=sumipi/sumpi;
        else
            m2=0;
        t1=(m1+m2)/2;
     //cout<<"Iterative threshold: "<<t1<<endl;
    }while(fabs(t1-t0)!=0);
    cout<<"Isodata threshold = "<<(int)t1;
}
