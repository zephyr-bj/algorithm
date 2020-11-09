#include <string>
using namespace std;

string intToRoman(int num) {
    string bin1="MCXI";
    string bin2=" DLV";
    vector<int> scale = {1000, 100, 10, 1};
    string ans;
    for(int i=0; i<4; i++){
        int n = num/scale[i];
        if(n==4){
            ans+=bin1[i];
            ans+=bin2[i];
        }else if(n==5){
            ans+=bin2[i];
        }else if(n>4 && n<9){
            ans+=bin2[i];
            string tmp(n-5,bin1[i]);
            ans+=tmp;
        }else if(n==9){
            ans+=bin1[i];
            ans+=bin1[i-1];
        }else{
            string tmp(n,bin1[i]);
            ans+=tmp;
        }
        num -= n*scale[i];
    }
    return ans;
}
