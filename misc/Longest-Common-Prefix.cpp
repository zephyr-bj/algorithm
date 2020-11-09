

#include <string>
using namespace std;
string longestCommonPrefix(vector<string>& strs) {
    if(strs.size()==0)return "";
    int anchor=0;
    for(int i=0; i<strs.size(); i++){
        if(strs[i].size()<strs[anchor].size())anchor=i;
    }
    string ans;
    for(int i=0; i<strs[anchor].size(); i++){
        bool common=true;
        for(int j=0; j<strs.size(); j++){
            if(strs[anchor][i]!=strs[j][i]){
                common=false;
                break;
            }
        }
        if(common==false)break;
        ans+=strs[anchor][i];
    }
    return ans;
}
