/*
 * Count-and-Say.cpp
 *
 *  Created on: Mar 4, 2017
 *      Author: Zephyr
 */
#include<vector>
using namespace std;

string countAndSay(int n) {
    string ans(1,'1');
    for(int i=1; i<n; i++){
        int x=0;int count=0;
        string tmp;
        for(int j=0; j<ans.size(); j++){
            if(ans[x]==ans[j]){
                count++;
            }else{
                tmp.push_back((j-x)+'0');
                tmp.push_back(ans[x]);
                x=j; count=0;
            }
        }
        tmp.push_back((ans.size()-x)+'0');
        tmp.push_back(ans[x]);
        ans=tmp;
    }
    return ans;
}

