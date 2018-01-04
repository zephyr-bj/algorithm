#include <vector>
using namespace std

void 2sum(int & idx1, int & idx2, int sum, vector<int>bin){
    int i=0;
    int j=bin.size()-1;
    while(i<j){
        if(bin[i]+bin[i]==sum){
            idx1=i; idx2=j;
            return;
        }else if(bin[i]+bin[j]<sum){
            i++;
        }else{
            j--;
        }
    }
    idx1=-1;
    idx2=-1;
} 
