#include "BloomFilter.h"
#include <iostream>
using namespace std;

int main(){
    int n = 100;
    for(int m = 200; m <=500;m+=100){
        cout<<"m = "<<m<<endl;
        for(int k = 1;k<=8; ++k){
            BloomFilter bf(n,m,k);

            for(int i = 0;i < n;i++)
                bf.insert(i);

            int fault = 0;
            for(int i = 100;i < 100100;i++)
                fault += bf.find(i);

            cout<<"k = "<<k<<"; faults:"<<fault<<' '<<fault/100000.<<endl;
        }
        cout<<endl;
    }


    return 0;
}