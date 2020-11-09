
#include <string>
using namespace std;

string convert(string s, int numRows) {
    if(numRows==1)return s;
    int n = s.size();
    int cycle = (numRows-1)*2;
    vector<string>bin(numRows,"");
    for(int i=0; i<n; i++){
        int idx = i%cycle;
        if(idx<numRows){
            bin[idx].push_back(s[i]);
        }else{
            bin[numRows-(idx-numRows)-2].push_back(s[i]);
        }
    }
    string ans("");
    for(int j=0; j<numRows; j++){
        ans+=bin[j];
    }
    return ans;
}
